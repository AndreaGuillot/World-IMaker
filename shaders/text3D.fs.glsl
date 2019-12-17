#version 330 core

// Input
in vec2 vFragPosition;
in vec2 vFragTexCoords;

// Output
out vec3 fFragColor;

// Uniform
uniform vec3 uColor;
uniform sampler2D uTexture;

void main()
{
	// output color 
	fFragColor = vec3(1.0, 0.0, 0.0);
}