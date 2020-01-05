#pragma once

#include <iostream>
#include <vector>
#include <ostream>
#include <fstream>
#include <glimac/common.hpp>
#include <eigen3/Eigen/Dense>

#include "RadialBasisFunctions.hpp"

using namespace glimac;

#define WORLD_TAILLE 40

/********************************
 *        CREATE 3D CUBE        *
 ********************************/

class Cubes
{
    protected:
        std::vector<ShapeVertex> m_vertex;
        std::vector<glm::vec3> m_position;
        std::vector<glm::vec4> m_color;
        GLuint vbo;
        GLuint vbPos;
        GLuint vbCol;
        GLuint vao;
        GLuint ibo;
        GLuint iboWireframe;

    public:
        // initialization
        Cubes();
        ~Cubes();
        // draw
        void drawCube();
        void drawCubeWireframe();
        void updateGPU();
        // color
        void editColor(glm::vec3 position, glm::vec4 color);
        inline std::vector<glm::vec4> getColors() const { return m_color; }
        inline glm::vec4 getLastColor() const { return m_color[m_color.size()-1]; }
        // sculpting
        int  findCube(glm::vec3 position);
        bool isCubeExist(glm::vec3 position);
        void removeCube(glm::vec3 position);
        void addCube(glm::vec3 position, glm::vec4 color);
        void extrudeCube(glm::vec3 position, glm::vec4 color);
        void digCube(glm::vec3 position);
        // procedural generation
        //void loadWorld();
        // save - load
        void saveScene(const std::string &filePath, const std::string &filename);
        void loadScene(const std::string &filePath, const std::string &filename);
        // delete all data
        void deleteData();
};