#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

layout (location = 0) out vec2 TexCoord;
layout (location = 1) out vec4 textureColor;
layout (location = 3) out vec3 normal;
layout (location = 4) out vec3 fragPos;
layout (location = 5) out mat3 normalMatrix;

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
	mat4 modelMatrix = model * root;
    gl_Position = proj * view * modelMatrix * vec4(position, 1.0f);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	textureColor = materialColor;
	TexCoord = aTexCoord;
	normal = aNormal;
	fragPos = vec3(model * vec4(position, 1.0));
	normalMatrix = transpose(inverse(mat3(model)));
}