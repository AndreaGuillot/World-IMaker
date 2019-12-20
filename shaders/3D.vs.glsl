#version 330 core

// Vertex attributes
layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aCubePosition;
layout(location = 2) in vec3 aNormal;

// Uniform : transformation matrix
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;


// Output
out vec3 vFragPosition;
out vec3 vNormal;

void main()
{
	// homogeneous coordinates
    vec4 position = vec4(aVertexPosition + aCubePosition, 1.0);
    // view coordinates
    vFragPosition = vec3(uMVMatrix * position);
    vNormal = aNormal;
    // projected position
    gl_Position = uMVPMatrix * position;
}