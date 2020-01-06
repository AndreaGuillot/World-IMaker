#include "../include/ShaderProgram.hpp"

ShaderProgram::ShaderProgram(const FilePath &applicationPath, std::string object)
    : m_program(loadProgram(applicationPath.dirPath() + "../shaders/3D.vs.glsl", applicationPath.dirPath() + "../shaders" + object))
{
    m_uMVPMatrix = glGetUniformLocation(m_program.getGLId(), "uMVPMatrix");
    m_uMVMatrix = glGetUniformLocation(m_program.getGLId(), "uMVMatrix");
    m_uNormalMatrix = glGetUniformLocation(m_program.getGLId(), "uNormalMatrix");
    m_uLightDir = glGetUniformLocation(m_program.getGLId(), "uLightDir");
    m_uTexture = glGetUniformLocation(m_program.getGLId(), "uTexture");
}

void ShaderProgram::useProgram()
{
	m_program.use();
}

void ShaderProgram::createViewMatrix(const TrackballCamera &camera) const
{   
    glm::mat4 ViewMatrix 	= camera.getViewMatrix();
    glm::mat4 ProjMatrix 	= glm::perspective(glm::radians(70.f), 5.f/4.f, 0.1f, 100.f);
    glm::mat4 MVMatrix 		= glm::translate(ViewMatrix, glm::vec3(0.f,0.f,0.f));
    glm::mat4 NormalMatrix 	= glm::transpose(glm::inverse(MVMatrix));
    glm::vec3 lightDir 		= glm::vec3(1.f, 1.f, 1.f);
    
    glUniformMatrix4fv(m_uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(m_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    glUniformMatrix4fv(m_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
    glUniform3fv(m_uLightDir, 1, glm::value_ptr(lightDir));
    glUniform1i(m_uTexture, 0);
}