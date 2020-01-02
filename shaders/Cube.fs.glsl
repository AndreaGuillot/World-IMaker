#version 330 core

// Input
in vec2 vFragTexture;
in vec3 vFragPosition;
in vec3 vNormal;
in vec4 vColor;

// Uniform
uniform vec3 uLightDir;
uniform vec3 uLightPos;
uniform sampler2D uTexture;

// Output
out vec4 fFragColor;

void main()
{
	// calcul light
	vec3 dir = normalize(vec3(0.5, -0.7, -0.8));
	vec3 pos = normalize(vec3(0.8, -0.5, -0.1));
	vec3 pos2 = normalize(vec3(-0.2, 0.2, -0.8));

	vec3 dirBetweenPointLightAndCurrentPixel = normalize(vFragPosition-pos);
	vec3 dirBetweenPointLightAndCurrentPixel2 = normalize(vFragPosition-pos2);
	
	float luminosityDirLight = max(-dot(vNormal, dir), 0.2);
	float luminosityPointLight = max(-dot(vNormal, dirBetweenPointLightAndCurrentPixel ), 0.2);
	float luminosityPointLight2 = max(-dot(vNormal, dirBetweenPointLightAndCurrentPixel2 ), 0.2);

	float totalLuminosity = min(luminosityDirLight + luminosityPointLight, 1.);
	float totalLuminosity2 = min(luminosityPointLight2 + luminosityPointLight, 1.);

	if(vColor != vec4(1.0, 1.0, 1.0, 1.0))
	{
		fFragColor = vec4(vColor * totalLuminosity2); 
	}
	
/*
	vec4 texture = texture(uTexture, vFragTexture);
  	fFragColor = vec3(texture);
*/
}