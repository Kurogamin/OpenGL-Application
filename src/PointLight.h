#pragma once

#include "Include.h"

class PointLight : public Light
{
private:
	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;
public:
	PointLight()
	{
		
	}
	PointLight(glm::vec3 position, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : Light(ambient, diffuse, specular)
	{
		this->position = position;
		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
	}

	void UpdateShaderLight(Shaders shader, std::string uniformName = "pointLight")
	{
		Light::UpdateShaderLight(shader, uniformName);
		shader.useShaders();
		shader.changeVec3Uniform(uniformName + ".position", position);
		shader.useShaders();
		shader.changeFloatUniform(uniformName + ".constant", constant);
		shader.useShaders();
		shader.changeFloatUniform(uniformName + ".linear", linear);
		shader.useShaders();
		shader.changeFloatUniform(uniformName + ".quadratic", quadratic);
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

	
};
