#pragma  once

#include <iostream>
#include <eigen3/Eigen/Dense>
#include "Cubes.hpp"
#include "RadialBasisFunctions.hpp"

using namespace glimac;

#define WORLD_TAILLE 20

class Map {
    protected:
    int m_nbPoints = 0;
    Eigen::MatrixXd m_map;
    Eigen::MatrixXf m_ControlPoints;
    Eigen::VectorXf m_values;

    public:
        // initialization
        Map() : m_map(WORLD_TAILLE, WORLD_TAILLE), m_ControlPoints(m_nbPoints, 2), m_values(m_nbPoints) {}
        ~Map() = default;
        // sculpting
        void initWorld(Cubes &cube);
        void deleteInitWorld(Cubes &cube);
        int  findControlPoint(float x, float z);
        bool isControlPointExist(float x, float z);
        void removeControlPoint(float x, float z);
        void addControlPoint(int x, int z, int poids);
        void loadWorld(Cubes &cube, glm::vec4 defaultColor);
        void clearWorld(Cubes &cube);
        void displayControlPoints();

};

