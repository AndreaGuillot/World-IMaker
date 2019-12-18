#include "../include/Curseur.hpp"

using namespace glimac;

void Curseur::deplacement(glm::vec3 direction){
	//m_cube.remove(m_position);
	m_position += direction;
	std::cout<<m_position<<std::endl;
	//m_cube.add(m_position);
}

void Curseur::drawCurseur()
{
    m_cube.drawCube();
}

void Curseur::onKeyPressed(SDL_Event e){
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