#version 330 core

// Input
in vec3 vNormal;
in vec4 vColor;

// Uniform
uniform vec3 uLightDir;

// Output
out vec4 fFragColor;

void main()
{
	// calcul light
	vec3 dir = normalize(vec3(0.5, -0.7, -0.8));
	float luminosite = max(-dot(vNormal, dir), 0.2);
	// color * light
	fFragColor = vColor * luminosite;
}