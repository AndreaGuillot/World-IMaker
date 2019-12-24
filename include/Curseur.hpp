#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <glimac/glm.hpp>
#include "Cubes.hpp"

/********************************
 *      CREATE A CUBE CURSOR    *
 ********************************/

class Curseur : public Cubes
{
	private :
		glm::vec3 m_posCursor;
		glm::vec4 m_colorCursor;

	public :
		// constructor
		Curseur() : m_posCursor(0.0f, 0.0f, 0.0f), m_colorCursor(1.f, 1.f, 1.f, 1.f) { addCube(m_posCursor, m_colorCursor); }
		// draw
		void drawCurseur();
		// movement
		void deplacement(glm::vec3 direction);
		void onKeyPressed(SDL_Event e);
		glm::vec3 getPosition() const { return m_posCursor; }
		// destructor
		~Curseur() = default;
};