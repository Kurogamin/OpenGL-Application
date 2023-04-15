#version 450 core
layout (location = 0) in vec3 position;

layout (location = 0) out vec4 textureColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec4 materialColor;
uniform mat4 rootMatrix;

void main()
{
    mat4 root = rootMatrix;
	if (root == mat4(0.0)) 
	{
		root = mat4(1.0);
	}
    mat4 modelMatrix = root * model;
    gl_Position = proj * view * modelMatrix * vec4(position, 1.0f);
    textureColor = materialColor;
}