#pragma once

#include "Include.h"

class DirectionalLight : public Light
{
private:
	glm::vec3 direction;
public:
	DirectionalLight()
	{
		
	}
	
	DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : Light(ambient, diffuse, specular)
	{
		this->direction = direction;
	}
	
	void UpdateShaderLight(Shaders shader, std::string uniformName = "dirLight")
	{
		Light::UpdateShaderLight(shader, uniformName);
		shader.useShaders();
		shader.changeVec3Uniform(uniformName + ".direction", this->direction);
	}

	void SetDirection(glm::vec3 direction)
	{
		this->direction = direction;
	}
};