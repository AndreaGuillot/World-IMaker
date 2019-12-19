#include "../include/Curseur.hpp"

/********************************
 *      CREATE A CUBE CURSOR    *
 ********************************/

void Curseur::linkShader(GLint &uMVPMatrix, GLint &uMVMatrix, GLint &uNormalMatrix, ShaderProgram &shader)
{
    uMVPMatrix = glGetUniformLocation(shader.m_program.getGLId(), "uMVPMatrix");
    uMVMatrix = glGetUniformLocation(shader.m_program.getGLId(), "uMVMatrix");
    uNormalMatrix = glGetUniformLocation(shader.m_program.getGLId(), "uNormalMatrix");
}

void Curseur::transformMatrix(GLint &uMVPMatrix, GLint &uMVMatrix, GLint &uNormalMatrix, const TrackballCamera &camera) const
{   
    glm::mat4 ViewMatrix = camera.getViewMatrix();
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 4.f/3.f, 0.1f, 100.f);
    glm::mat4 MVMatrix = glm::translate(ViewMatrix, glm::vec3(0.f,0.f,0.f));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    
    glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
}

void Curseur::deplacement(glm::vec3 direction)
{
	m_cube.removeCube(m_position);
	m_position += direction;
	m_cube.addCube(m_position);
}

void Curseur::drawCurseur()
{
    m_cube.drawCubeWireframe();
}

void Curseur::onKeyPressed(SDL_Event e)
{
	glm::vec3 direction = glm::vec3(0.f, 0.f, 0.f);
	switch (e.key.keysym.sym) {
		case SDLK_UP :
			direction = glm::vec3(0.f, 1.f, 0.f);
			break;
		case SDLK_DOWN :
			direction = glm::vec3(0.f, -1.f, 0.f);
			break;
		case SDLK_LEFT :
			direction = glm::vec3(-1.f, 0.f, 0.f);
			break;
		case SDLK_RIGHT :
			direction = glm::vec3(1.f, 0.f, 0.f);
			break;
		case SDLK_p :
			direction = glm::vec3(0.f, 0.f, -1.f);
			break;
		case SDLK_m :
			direction = glm::vec3(0.f, 0.f, 1.f);
			break;
		default:
			break;

	}

	deplacement(direction);

}