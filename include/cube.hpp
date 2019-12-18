#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "../lib/glimac/include/glimac/glm.hpp"
#include "../lib/glimac/include/glimac/common.hpp"
#include "../lib/glimac/include/glimac/FilePath.hpp"
#include "../lib/glimac/include/glimac/Program.hpp"

using namespace glimac;

/********************************
 *       CREATE A 3D CUBE       *
 ********************************/

class Cube {
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
        Cube();
        void drawCube();
        void drawCubeWireframe();
        void updateGPU();
        int findCube(glm::vec3 position);
        void removeCube(glm::vec3 position);
        void addCube(glm::vec3 position);
        void deleteData();
        ~Cube();
};