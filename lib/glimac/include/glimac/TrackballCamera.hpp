#include <GL/glew.h>
#include "glm.hpp"

class TrackballCamera
{
    private : 
        float m_fDistance;  // Distance par rapport au centre de la scène
        float m_fAngleX;    // Angle effectué par la cam autour de l'axe X (gauche/droite)
        float m_fAngleY;    // Angle effectué par la cam autour de l'axe Y (haut/bas)

    public :
        // constructor
        TrackballCamera() : m_fDistance(5.f), m_fAngleX(0.f), m_fAngleY(0.f) {}
        // movement
        void moveFront(float delta){m_fDistance += delta;}      // avance - recule
        void rotateLeft(float degrees){m_fAngleY += degrees;}   // tourne latéralement
        void rotateUp (float degrees){m_fAngleX += degrees;}    // tourne verticalement
        // calculate camera ViewMatrix
        glm::mat4 getViewMatrix() const
        {
            glm::mat4 ViewMatrix;
            ViewMatrix = glm::translate(glm::mat4(1), glm::vec3(0.f, 0.f, m_fDistance));
            ViewMatrix = glm::rotate(ViewMatrix, glm::radians(m_fAngleX), glm::vec3(1.f, 0.f, 0.f));
            ViewMatrix = glm::rotate(ViewMatrix, glm::radians(m_fAngleY), glm::vec3(0.f, 1.f, 0.f));
            return ViewMatrix;      
        }

};