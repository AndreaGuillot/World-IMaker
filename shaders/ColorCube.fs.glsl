#version 330 core


//Uniform light
uniform vec3 uLightDir; 

// Input
in vec3 vFragPosition;
in vec3 vNormal;

// Output
out vec3 fFragColor;

void main()
{
	// output color
	vec3 dir = normalize(vec3(0.5, -0.7, -0.8));
	float luminosite = max(-dot(vNormal, dir), 0.2);
	fFragColor = vec3(0.8, 0.2, 0.3) * luminosite;
}