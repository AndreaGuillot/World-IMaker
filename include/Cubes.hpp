#pragma once

#include <iostream>
#include <vector>
#include <ostream>
#include <fstream>
#include <glimac/common.hpp>
#include <eigen3/Eigen/Dense>

#include "RadialBasisFunctions.hpp"
#include "Texture.hpp"

using namespace glimac;

#define WORLD_TAILLE 20

/********************************
 *        CREATE 3D CUBE        *
 ********************************/

class Cubes
{
    protected:
        Texture* texture;

        std::vector<ShapeVertex> m_vertex;
        std::vector<glm::vec3> m_position;
        std::vector<glm::vec4> m_color;
        std::vector<int> m_texture;

        int m_type;

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
        // sculpting
        int  findCube(glm::vec3 position);
        bool isCubeExist(glm::vec3 position);
        void removeCube(glm::vec3 position);
        void addCube(glm::vec3 position, glm::vec4 color, int type);
        void extrudeCube(glm::vec3 position, glm::vec4 color, int type);
        void digCube(glm::vec3 position);
        // texture
        void editTexture(glm::vec3 position, int type);
        Texture* addTexture();
        // save - load
        void saveScene(const std::string &filePath, const std::string &filename);
        void loadScene(const std::string &filePath, const std::string &filename);
        // delete all data
        void deleteData();
        // getters
        inline std::vector<glm::vec4> getColors() const { return m_color; }
        inline glm::vec4 getLastColor() const { return m_color[m_color.size()-1]; }
        inline std::vector<glm::vec3> getPosition() const { return m_position; }
        inline std::vector<int> getTexture() const { return m_texture; }
};