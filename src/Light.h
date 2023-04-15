#pragma once

#include "Include.h"

class Light
{
protected:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
public:
	Light()
	{
		
	}
	
	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
	{
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
	}
	
	void UpdateShaderLight(Shaders shader, std::string uniformName)
	{
		shader.useShaders();
		shader.changeVec3Uniform(uniformName + ".ambient", ambient);
		shader.useShaders();
		shader.changeVec3Uniform(uniformName + ".diffuse", diffuse);
		shader.useShaders();
		shader.changeVec3Uniform(uniformName + ".specular", specular);
	}

	static void DisableLight(Shaders shader, std::string uniformName)
	{
		shader.useShaders();
		shader.changeVec3Uniform(uniformName + ".ambient", glm::vec3(0.0f));
		shader.useShaders();
		shader.changeVec3Uniform(uniformName + ".diffuse", glm::vec3(0.0f));
		shader.useShaders();
		shader.changeVec3Uniform(uniformName + ".specular", glm::vec3(0.0f));
	}

	void SetAmbient(glm::vec3 ambient)
	{
		this->ambient = ambient;
	}

	void SetDiffuse(glm::vec3 diffuse)
	{
		this->diffuse = diffuse;
	}

	void SetSpecular(glm::vec3 specular)
	{
		this->specular = specular;
	}
};