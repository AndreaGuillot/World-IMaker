#pragma once

#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include "TrackballCamera.hpp"

using namespace glimac;

/********************************
 *        GENERATE SHADERS      *
 ********************************/

class ShaderProgram
{
    private:
        Program m_program;
        GLint m_uMVPMatrix;
        GLint m_uMVMatrix;
        GLint m_uNormalMatrix;
        GLint m_uLightDir;
        GLint m_uTexture;

    public:
        ShaderProgram(const FilePath &applicationPath, std::string object);
        ~ShaderProgram() = default;
        void useProgram();
        void createViewMatrix(const TrackballCamera &camera) const;

};