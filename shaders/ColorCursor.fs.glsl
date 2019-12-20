#version 330 core

// Input
in vec2 vFragPosition;

// Output
out vec3 fFragColor;

uniform vec3 uLightDir; 

void main()
{
	// output color 
	fFragColor = vec3(1.0f, 1.0f, 1.0f);
}