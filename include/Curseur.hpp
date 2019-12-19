#pragma once

#include <SDL/SDL.h>
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

	public :
		// constructor
		Curseur() : m_posCursor(0.0f, 0.0f, 0.0f) { addCube(m_posCursor); }
		// draw
		void drawCurseur();
		// movement
		void deplacement(glm::vec3 direction);
		void onKeyPressed(SDL_Event e);
		glm::vec3 getPosition () const { return m_posCursor; }
		// destructor
		~Curseur() = default;
};