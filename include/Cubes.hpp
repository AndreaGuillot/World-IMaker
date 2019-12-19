#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <glimac/glm.hpp>
#include <glimac/common.hpp>
#include <glimac/Program.hpp>
#include "ShaderProgram.hpp"

using namespace glimac;

/********************************
 *       CREATE A 3D CUBE       *
 ********************************/

class Cubes
{
    private:
        std::vector<ShapeVertex> m_vertex;
        std::vector<glm::vec3> m_posCubes;

        GLuint vbo;
        GLuint vbPos;
        GLuint vao;
        GLuint ibo;
        GLuint iboWireframe;

    public:
        // constructor
        Cubes();
        void linkShader(GLint &uMVPMatrix, GLint &uMVMatrix, GLint &uNormalMatrix, ShaderProgram &shader);
        // draw
        void drawCube();
        void drawCubeWireframe();
        void updateGPU();
        // cube
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