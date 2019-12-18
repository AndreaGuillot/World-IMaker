#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <glimac/glm.hpp>
#include <glimac/common.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>

using namespace glimac;

/********************************
 *       CREATE A 3D CUBE       *
 ********************************/

class Cubes
{
    private:
        std::vector<ShapeVertex> m_vertex;
        std::vector<glm::vec3> posCubes;
        GLuint vbo;
        GLuint vbPos;
        GLuint vao;
        GLuint ibo;
        GLuint iboWireframe;
        std::string shader;

    public:
        // constructor
        Cubes();
        // draw
        void drawCube();
        void drawCubeWireframe();
        void updateGPU();
        // cube
        int findCube(glm::vec3 position);
        void removeCube(glm::vec3 position);
        void addCube(glm::vec3 position);
        // delete data
        void deleteData();
        // destructor
        ~Cubes();
};