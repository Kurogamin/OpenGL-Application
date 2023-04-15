#version 450 core
out vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec4 materialColor;

void main()
{
    color = materialColor;
}