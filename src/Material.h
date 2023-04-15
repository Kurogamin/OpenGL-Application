#pragma once

#include "Include.h"

class Material
{
private:
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec3 specular;
	float shininess;
public:
	Material()
	{
		
	}
	
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
	{
		this->ambient = glm::vec4(ambient, 1.0f);
		this->diffuse = glm::vec4(diffuse, 1.0f);
		this->specular = glm::vec4(specular, 1.0f);
		this->shininess = shininess;
	}

	Material(int r, int g, int b, glm::vec3 specular, float shininess)
	{
		this->ambient = glm::vec4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
		this->diffuse = glm::vec4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
		this->specular = glm::vec4(specular, 1.0f);
		this->shininess = shininess;
	}

	void UpdateShaderMaterial(Shaders shader)
	{
		shader.useShaders();
		shader.changeVec4Uniform("material.ambient", ambient);
		shader.changeVec4Uniform("material.diffuse", diffuse);
		shader.changeVec3Uniform("material.specular", specular);
		shader.changeFloatUniform("material.shininess", shininess);
	}
};