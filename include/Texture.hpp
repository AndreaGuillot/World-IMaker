#pragma once

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <glimac/Image.hpp>
#include "ShaderProgram.hpp"

using namespace glimac;

class Texture
{
	private:
		GLuint m_textureID;
		std::unique_ptr<Image> imgPointer;
		std::string m_path;

	public:
		// initialization
		Texture(std::string name);
		~Texture();
		// texture
		void bindTexture();
		void unbindTexture();
		void setTexturePath(std::string path);
};