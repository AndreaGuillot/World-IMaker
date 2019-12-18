#ifndef CURSEUR__HPP
#define CURSEUR__HPP
#pragma once

#include <iostream>
#include <SDL/SDL.h>
#include "../lib/glimac/include/glimac/glm.hpp"
#include "cube.hpp"


class Curseur {
	private :
		glm::vec3 m_position;
		Cube m_cube;

	public :
		Curseur() : m_position(0.f, 0.f, 0.f) {}
		void drawCurseur();
		void deplacement(glm::vec3 direction);
		void onKeyPressed(SDL_Event e);

};

#endif