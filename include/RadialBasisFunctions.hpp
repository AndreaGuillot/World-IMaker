#pragma once

#include <iostream>
#include <eigen3/Eigen/Dense>

#define WORLD_TAILLE 40

float phi(const float a);
Eigen::MatrixXd getMap (const Eigen::MatrixXf ControlPoints, const Eigen::VectorXf values);
Eigen::VectorXf findOmega (const Eigen::MatrixXf ControlPoints, const Eigen::VectorXf values);
int findValue(const int i, const int j, const Eigen::MatrixXf ControlPoints, const Eigen::VectorXf w);


