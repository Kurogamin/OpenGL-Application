#pragma once 

#include "Include.h"

class DirectionalLightCube : public LightCube
{
private:
	DirectionalLight light;
	DirectionLine line;
	int option = -1;
public:
	DirectionalLightCube() : LightCube()
	{
		this->line.transform.pos = this->transform.pos;
		this->line.transform.eulerRot = this->transform.eulerRot;
		this->line.transform.scale.z = -1.0f;
	}

	void UpdateShaderLight(Shaders shader, std::string uniformName = "dirLight")
	{
		this->color = glm::vec4(this->diffuse, 1.0f);
		SetLightProperties();
		this->line.SetColor(this->color);
		this->light.UpdateShaderLight(shader, uniformName);
	}

	void SetLightProperties()
	{
		this->light.SetAmbient(ambient);
		this->light.SetDiffuse(diffuse);
		this->light.SetSpecular(specular);
		this->light.SetDirection(this->transform.GetDirection());
	}

	void Draw()
	{
		LightCube::Draw();
		this->line.SetProjectionMatrix(this->projectionMatrix);
		this->line.SetViewMatrix(this->viewMatrix);
		this->line.Draw(this->rootTransform->GetLocalModelMatrix() * this->transform.GetLocalModelMatrix());
	}
	
	void Gui()
	{
		if (ImGui::CollapsingHeader("Direction Light", 26))
		{
			if (ImGui::Button("Direction")) option = 0;
			if (ImGui::Button("Ambient")) option = 1;
			if (ImGui::Button("Diffuse")) option = 2;
			if (ImGui::Button("Specular")) option = 3;

			switch (option)
			{
			case 0:
				ImGui::DragFloat3("Direction", (float*)&transform.eulerRot);
				break;
			case 1:
				ImGui::DragFloat3("Ambient", (float*)&ambient, 0.01f, 0.0f, 1.0f);
				break;
			case 2:
				ImGui::DragFloat3("Diffuse", (float*)&diffuse, 0.01f, 0.0f, 1.0f);
				break;
			case 3:
				ImGui::DragFloat3("Specular", (float*)&specular, 0.01f, 0.0f, 1.0f);
				break;
			}
		}
	}
};
