#include "../include//Texture.hpp"

Texture::Texture(std::string name)
{   
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
        setTexturePath(name);
        imgPointer = loadImage("assets/textures/" + m_path);
        if(imgPointer == NULL)
        {
            std::cerr << "ERREUR : Impossible de charger la texture " << name << "." << std::endl;
        }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgPointer->getWidth(), imgPointer->getHeight(), 0, GL_RGBA, GL_FLOAT, imgPointer->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_textureID);
}

void Texture::bindTexture()
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);	
}

void Texture::setTexturePath(std::string name)
{
    if(name == "grass")     m_path = "grass/grass_top.png";
    else if(name == "ice")  m_path = "ice/ice.png";
    else if(name == "sand") m_path = "sand/sand.png";
    else                    m_path = "no_texture.jpg";
}