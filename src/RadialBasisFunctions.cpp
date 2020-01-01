#include "../include/RadialBasisFunctions.hpp"

float phi(const float a){
    return exp(-0.2*a*a);
}

Eigen::VectorXf findOmega (const Eigen::MatrixXf ControlPoints, const Eigen::VectorXf values){

    Eigen::MatrixXf A = Eigen::MatrixXf::Zero(ControlPoints.rows(), ControlPoints.rows());
    for(int i=0; i<A.rows(); ++i){
        for(int j=0; j<A.cols(); ++j){
            A(i,j) = phi(
                (ControlPoints.row(i) - ControlPoints.row(j)).norm()
                );
        }
    }
    return A.inverse() * values;
}

int findValue(const int i, const int j, const Eigen::MatrixXf ControlPoints, const Eigen::VectorXf w){

    float value = 0;
    Eigen::VectorXf point(2);
    point << i, j;

    for(int index=0; index < ControlPoints.rows(); ++index){
        value += w(index) * phi(
                (point.transpose() - ControlPoints.row(index)).norm()
            );
    }
    return round(value);

}


Eigen::MatrixXd getMap(const Eigen::MatrixXf ControlPoints, const Eigen::VectorXf valeurs){
    Eigen::VectorXf w = findOmega(ControlPoints, valeurs);
    Eigen::MatrixXd map = Eigen::MatrixXd::Zero(WORLD_TAILLE, WORLD_TAILLE);

    for(int i=0; i<map.rows(); ++i){
        for(int j=0; j<map.cols(); ++j){
            map(i,j) = findValue(i, j, ControlPoints, w);
        }
    }

    return map;
}




