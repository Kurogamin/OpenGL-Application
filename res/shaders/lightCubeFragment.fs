#version 450 core
layout (location = 0) in vec4 textureColor;
out vec4 color;

void main()
{
   color = textureColor;
}
  