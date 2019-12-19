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
		Curseur() : m_position(0.0f, 0.0f, 0.0f) { m_cube.addCube(m_position); }
		// draw
		void linkShader(GLint &uMVPMatrix, GLint &uMVMatrix, GLint &uNormalMatrix, ShaderProgram &shader);
		void transformMatrix(GLint &uMVPMatrix, GLint &uMVMatrix, GLint &uNormalMatrix, const TrackballCamera &camera) const;
		void drawCurseur();
		// movement
		void deplacement(glm::vec3 direction);
		void onKeyPressed(SDL_Event e);
		glm::vec3 getPosition () const { return m_position; }
		// destructor
		~Curseur() = default;
};