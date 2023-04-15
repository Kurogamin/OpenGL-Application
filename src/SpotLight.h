#pragma once

#include "Include.h"

class SpotLight : public Light
{
private:
	glm::vec3 position;
	glm::vec3 direction;
	float constant;
	float linear;
	float quadratic;
	float cutOff;
	float outerCutOff;
public:
	
	SpotLight()
	{
		
	}
	
	SpotLight(float cutOff, float outerCutOff, float constant, float linear, float quadratic, glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : Light(ambient, diffuse, specular)
	{
		this->cutOff = cutOff;
		this->outerCutOff = outerCutOff;
		this->position = position;
		this->direction = direction;
		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
	}

	void UpdateShaderLight(Shaders shader, std::string uniformName = "spotLights[0]")
	{
		Light::UpdateShaderLight(shader, uniformName);
		shader.changeVec3Uniform(uniformName + ".position", position);
		shader.changeVec3Uniform(uniformName + ".direction", direction);
		shader.changeFloatUniform(uniformName + ".cutOff", cutOff);
		shader.changeFloatUniform(uniformName + ".outerCutOff", outerCutOff);
		shader.changeFloatUniform(uniformName + ".constant", constant);
		shader.changeFloatUniform(uniformName + ".linear", linear);
		shader.changeFloatUniform(uniformName + ".quadratic", quadratic);
	}

	void SetDirection(glm::vec3 direction)
	{
		this->direction = direction;
	}

	void SetPosition(glm::vec3 position)
	{
		this->position = position;
	}
	
	void SetConstant(float constant)
	{
		this->constant = constant;
	}

	void SetLinear(float linear)
	{
		this->linear = linear;
	}

	void SetQuadratic(float quadratic)
	{
		this->quadratic = quadratic;
	}

	void SetCutOff(float cutOff)
	{
		this->cutOff = glm::cos(glm::radians(cutOff));
	}

	void SetOuterCutOff(float outerCutOff)
	{
		this->outerCutOff = glm::cos(glm::radians(outerCutOff));
	}
};