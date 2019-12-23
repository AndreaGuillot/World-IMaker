#version 330 core

// Uniform Light
uniform vec3 uLightDir; 

// Output
out vec4 fFragColor;

void main()
{
	// output color 
	fFragColor = vec4(1.0, 1.0, 1.0, 1.0);
}