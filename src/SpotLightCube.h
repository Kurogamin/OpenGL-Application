#pragma once 

#include "Include.h"

class SpotLightCube : public LightCube
{
private:
	SpotLight light;
	DirectionLine line;
	glm::vec3 direction;
public:
	SpotLightCube() : LightCube()
	{
		this->ambient = 0.05f * glm::vec3(1.0f, 1.0f, 1.0f);
		this->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
		this->specular = 1.0f * glm::vec3(1.0f, 1.0f, 1.0f);

		this->line.transform.pos = this->transform.pos;
		this->line.transform.eulerRot = this->transform.eulerRot;
	}

	void SetDirection(glm::vec3 newDirection)
	{
		this->direction = newDirection;
	}
	void UpdateShaderLight(Shaders shader, std::string uniformName = "spotLights[0]")
	{
		this->color = glm::vec4(this->diffuse, 1.0f);
		SetLightProperties();
		this->line.SetColor(this->color);
		this->light.UpdateShaderLight(shader, uniformName);
	}

	void SetLightProperties()
	{
		Transform t;
		t.eulerRot = this->transform.eulerRot;
		glm::vec4 pos4 = glm::vec4(this->transform.pos, 1.0f);
		glm::vec4 newPos = this->model * pos4;
		glm::vec3 finalPos = glm::vec3(newPos.x, newPos.y, newPos.z);
		
		this->light.SetAmbient(ambient);
		this->light.SetDiffuse(diffuse);
		this->light.SetSpecular(specular);
		this->light.SetDirection(this->direction);
		this->light.SetPosition(finalPos);
		this->light.SetConstant(constant);
		this->light.SetLinear(linear);
		this->light.SetQuadratic(quadratic);
		this->light.SetCutOff(cutOff);
		this->light.SetOuterCutOff(outerCutOff);
	}

	void Draw()
	{
		LightCube::Draw();
		this->line.SetProjectionMatrix(this->projectionMatrix);
		this->line.SetViewMatrix(this->viewMatrix);
		this->line.Draw(this->transform.GetLocalModelMatrix());
	}

	void Draw(glm::mat4 current, glm::mat4 parent)
	{
		LightCube::Draw(current, parent);
		this->line.SetProjectionMatrix(this->projection);
		this->line.SetViewMatrix(this->view);
		this->line.Draw(current);
	}

	void SetProjectionMatrix(glm::mat4 proj)
	{
		this->projectionMatrix = proj;
	}

	void SetViewMatrix(glm::mat4 view)
	{
		this->viewMatrix = view;
	}
};
