#include "../include/Curseur.hpp"

/********************************
 *      CREATE A CUBE CURSOR    *
 ********************************/

void Curseur::deplacement(glm::vec3 direction)
{
	removeCube(m_posCursor);
	m_posCursor += direction;
	addCube(m_posCursor);
}

void Curseur::drawCurseur()
{
    drawCubeWireframe();
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