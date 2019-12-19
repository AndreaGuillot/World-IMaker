#pragma once

#include <SDL/SDL.h>
#include <iostream>

#include <glimac/glm.hpp>

#include "Cubes.hpp"

/********************************
 *      CREATE A CUBE CURSOR    *
 ********************************/

class Curseur
{
	private :
		glm::vec3 m_position;
		Cubes m_cube;

	public :
		// constructor
		Curseur() : m_position(0.0f, 0.0f, 0.0f) {}
		void linkShader(GLint &uMVPMatrix, GLint &uMVMatrix, GLint &uNormalMatrix, ShaderProgram &shader);
		// draw
		void drawCurseur();
		// movement
		void deplacement(glm::vec3 direction);
		void onKeyPressed(SDL_Event e);
		glm::vec3 getPosition () const { return m_position; }

		// destructor
		~Curseur();
};