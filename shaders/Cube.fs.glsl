#version 330 core

// Input
in vec2 vFragTexture;
in vec3 vFragPosition;
in vec3 vNormal;
in vec4 vColor;

// Uniform
uniform vec3 uLightDir;
uniform sampler2D uTexture;

// Output
out vec4 fFragColor;

void main()
{
	// calcul light
	vec3 dir = normalize(vec3(0.5, -0.7, -0.8));
	float luminosite = max(-dot(vNormal, dir), 0.2);

	if(vColor != vec4(1.0, 1.0, 1.0, 1.0))
	{
		fFragColor = vColor * luminosite;
	}
	
/*
	vec4 texture = texture(uTexture, vFragTexture);
  	fFragColor = vec3(texture);
*/
}