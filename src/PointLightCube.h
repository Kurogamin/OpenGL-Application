#pragma once

#include "Include.h"

class PointLightCube : public LightCube
{
private:
	PointLight light;
public:
	PointLightCube() : LightCube()
	{
		this->ambient = 0.05f * glm::vec3(1.0f, 1.0f, 1.0f);
		this->diffuse = 0.8f * glm::vec3(1.0f, 1.0f, 1.0f);
		this->specular = 1.0f * glm::vec3(1.0f, 1.0f, 1.0f);
		this->constant = 1.0f;
		this->linear = 0.09f;
		this->quadratic = 0.032f;
	}

	void UpdateShaderLight(Shaders shader, std::string uniformName = "pointLight")
	{
		this->color = glm::vec4(this->diffuse, 1.0f);
		SetLightProperties();
		this->light.UpdateShaderLight(shader, uniformName);
	}

	void SetLightProperties()
	{
		this->light.SetAmbient(ambient);
		this->light.SetDiffuse(diffuse);
		this->light.SetSpecular(specular);
		this->light.SetPosition(this->transform.pos);
		this->light.SetConstant(constant);
		this->light.SetLinear(linear);
		this->light.SetQuadratic(quadratic);
	}
};