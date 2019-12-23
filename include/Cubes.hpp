#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <glimac/glm.hpp>
#include <glimac/common.hpp>
#include <glimac/Program.hpp>
#include "ShaderProgram.hpp"
#include "TrackballCamera.hpp"

using namespace glimac;

/********************************
 *       CREATE A 3D CUBE       *
 ********************************/

class Cubes
{
    protected:
        std::vector<ShapeVertex> m_vertex;
        std::vector<glm::vec3> m_position;

        GLuint vbo;
        GLuint vbPos;
        GLuint vao;
        GLuint ibo;
        GLuint iboWireframe;

    public:
        // constructor
        Cubes();
        // draw
        void getLocation(GLint &uMVPMatrix, GLint &uMVMatrix, GLint &uNormalMatrix, GLint &uLightDir, ShaderProgram &shader);
        void transformMatrix(GLint &uMVPMatrix, GLint &uMVMatrix, GLint &uNormalMatrix, GLint &uLightDir, const TrackballCamera &camera) const;
        void drawCube();
        void drawCubeWireframe();
        void updateGPU();
        // sculpting
        int findCube(glm::vec3 position);
        void removeCube(glm::vec3 position);
        void addCube(glm::vec3 position);
        void extrudeCube(glm::vec3 position);
        void digCube(glm::vec3 position);
        // delete data
        void deleteData();
        // destructor
        ~Cubes();
};