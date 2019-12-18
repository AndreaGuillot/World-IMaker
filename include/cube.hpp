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
        std::vector<glimac::ShapeVertex> m_vertex;
        GLuint vbo;
        GLuint vbPos;
        GLuint vao;
        GLuint ibo;
        std::string shader;

    public:
        Cube(FilePath applicationPath);
        void drawCube();
        void deleteData();
        ~Cube();
};