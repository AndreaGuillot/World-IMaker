#version 330 core

// Input
in vec3 vNormal;

// Uniform light
uniform vec3 uLightDir;

// Output
out vec4 fFragColor;

void main()
{
	// calcul light
	vec3 dir = normalize(vec3(0.5, -0.7, -0.8));
	float luminosite = max(-dot(vNormal, dir), 0.2);
	// output color * light
	fFragColor = vec4(0.8, 0.2, 0.3, 1.0) * luminosite;
}