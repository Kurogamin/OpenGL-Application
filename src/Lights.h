#pragma once

#include "Include.h"

class Lights
{
private:
	int dirOption = -1;
	int spotOptions[2];
	int pointOption = -1;

	bool dirLight = true;
	bool spotLights[2];
	bool pointLight = false;

	bool pointLightFlying = false;

	float oldRadius = 10.0f;
	float radius = 10.0f;
	float angle = 0.0f;

	glm::vec3 pointStartPosition = glm::vec3(200.0f, 3.0f, 200.0f);
	
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	Shaders housesShader;
	Shaders floorShader;
public:
	DirectionalLightCube* dirLightCube;
	SpotLightCube* spotLightCubes[2];
	PointLightCube* pointLightCube;
	Transform* rootTransform;

	Lights(DirectionalLightCube* dCube, SpotLightCube* sCube, SpotLightCube* sCube2, PointLightCube* pCube)
	{
		dirLightCube = dCube;
		spotLightCubes[0] = sCube;
		spotLightCubes[1] = sCube2;
		pointLightCube = pCube;
		spotLights[0] = false;
		spotLights[1] = false;
		spotOptions[0] = -1;
		spotOptions[1] = -1;
		dirLightCube->transform.ChangePosition(glm::vec3(0.0f, 20.0f, 0.0f));
		spotLightCubes[1]->transform.AddRotation(glm::vec3(0.0f, -90.0f, 0.0f));
	}

	void DirectionalLightGui()
	{
		if (ImGui::CollapsingHeader("Direction Light", 26))
		{
			ImGui::Checkbox("Direction Light", &dirLight);
			if (ImGui::Button("Switch Light"))
			{
				dirOption = -1;
				dirLight = !dirLight;
				Light::DisableLight(housesShader, "dirLight");
				Light::DisableLight(floorShader, "dirLight");
			}
			if (ImGui::Button("Direction")) dirOption = 0;
			if (ImGui::Button("Ambient")) dirOption = 1;
			if (ImGui::Button("Diffuse")) dirOption = 2;
			if (ImGui::Button("Specular")) dirOption = 3;

			switch (dirOption)
			{
			case 0:
				ImGui::DragFloat3("Direction", (float*)&dirLightCube->transform.eulerRot);
				break;
			case 1:
				ImGui::DragFloat3("Ambient", (float*)&dirLightCube->ambient, 0.01f, 0.0f, 1.0f);
				break;
			case 2:
				ImGui::DragFloat3("Diffuse", (float*)&dirLightCube->diffuse, 0.01f, 0.0f, 1.0f);
				break;
			case 3:
				ImGui::DragFloat3("Specular", (float*)&dirLightCube->specular, 0.01f, 0.0f, 1.0f);
				break;
			}
		}
	}

	void SpotLightGui(int index = 0)
	{
		if (ImGui::CollapsingHeader(("Spot Light " + std::to_string(index)).c_str(), 26))
		{
			ImGui::Checkbox(("Spot Light " + std::to_string(index)).c_str(), &spotLights[index]);
			if (ImGui::Button(("Switch Light " + std::to_string(index)).c_str()))
			{
				spotOptions[index] = -1;
				spotLights[index] = !spotLights[index];
				Light::DisableLight(housesShader, ("spotLights[" + std::to_string(index) + "]").c_str());
				Light::DisableLight(floorShader, ("spotLights[" + std::to_string(index) + "]").c_str());
			}
			if (ImGui::Button(("Position s" + std::to_string(index)).c_str())) spotOptions[index] = 0;
			if (ImGui::Button(("Rotation s" + std::to_string(index)).c_str())) spotOptions[index] = 1;
			if (ImGui::Button(("Ambient s" + std::to_string(index)).c_str())) spotOptions[index] = 2;
			if (ImGui::Button(("Diffuse s" + std::to_string(index)).c_str())) spotOptions[index] = 3;
			if (ImGui::Button(("Specular s" + std::to_string(index)).c_str())) spotOptions[index] = 4;
			if (ImGui::Button(("Constant s" + std::to_string(index)).c_str())) spotOptions[index] = 5;
			if (ImGui::Button(("Linear s" + std::to_string(index)).c_str())) spotOptions[index] = 6;
			if (ImGui::Button(("Quadratic s" + std::to_string(index)).c_str())) spotOptions[index] = 7;
			if (ImGui::Button(("CutOff s" + std::to_string(index)).c_str())) spotOptions[index] = 8;
			if (ImGui::Button(("OuterCutOff s" + std::to_string(index)).c_str())) spotOptions[index] = 9;

			switch (spotOptions[index])
			{
			case 0:
				ImGui::DragFloat3("Position", (float*)&spotLightCubes[index]->transform.pos);
				break;
			case 1:
				ImGui::DragFloat3("Rotation", (float*)&spotLightCubes[index]->transform.eulerRot);
				break;
			case 2:
				ImGui::DragFloat3("Ambient", (float*)&spotLightCubes[index]->ambient, 0.01f, 0.0f, 1.0f);
				break;
			case 3:
				ImGui::DragFloat3("Diffuse", (float*)&spotLightCubes[index]->diffuse, 0.01f, 0.0f, 1.0f);
				break;
			case 4:
				ImGui::DragFloat3("Specular", (float*)&spotLightCubes[index]->specular, 0.01f, 0.0f, 1.0f);
				break;
			case 5:
				ImGui::DragFloat("Constant", &spotLightCubes[index]->constant, 0.01f, 0.0f, 1.0f);
				break;
			case 6:
				ImGui::DragFloat("Linear", &spotLightCubes[index]->linear, 0.001f, 0.0f, 1.0f);
				break;
			case 7:
				ImGui::DragFloat("Quadratic", &spotLightCubes[index]->quadratic, 0.001f, 0.0f, 1.0f);
				break;
			case 8:
				ImGui::DragFloat("CutOff", &spotLightCubes[index]->cutOff, 1.0f, 0.0f, 90.0f);
				break;
			case 9:
				ImGui::DragFloat("OuterCutOff", &spotLightCubes[index]->outerCutOff, 1.0f, 0.0f, 90.0f);
				break;
			}
		}
	}

	void PointLightGui()
	{
		if (ImGui::CollapsingHeader("Point Light", 26))
		{
			ImGui::Checkbox("Point Light", &pointLight);
			if (ImGui::Button("Switch Light"))
			{
				pointOption = -1;
				pointLight = !pointLight;
				Light::DisableLight(housesShader, "pointLight");
				Light::DisableLight(floorShader, "pointLight");
			}
			if (ImGui::Button("Switch flying"))
			{
				pointLightFlying = !pointLightFlying;
			}
			if (ImGui::Button("Position p")) pointOption = 0;
			if (ImGui::Button("Ambient p")) pointOption = 1;
			if (ImGui::Button("Diffuse p")) pointOption = 2;
			if (ImGui::Button("Specular p")) pointOption = 3;
			if (ImGui::Button("Constant p")) pointOption = 4;
			if (ImGui::Button("Linear p")) pointOption = 5;
			if (ImGui::Button("Quadratic p")) pointOption = 6;
			if (ImGui::Button("Radius")) pointOption = 7;
			if (ImGui::Button("Start Position")) pointOption = 8;

			switch (pointOption)
			{
			case 0:
				ImGui::DragFloat3("Position", (float*)&pointLightCube->transform.pos);
				break;
			case 1:
				ImGui::DragFloat3("Ambient", (float*)&pointLightCube->ambient, 0.01f, 0.0f, 1.0f);
				break;
			case 2:
				ImGui::DragFloat3("Diffuse", (float*)&pointLightCube->diffuse, 0.01f, 0.0f, 1.0f);
				break;
			case 3:
				ImGui::DragFloat3("Specular", (float*)&pointLightCube->specular, 0.01f, 0.0f, 1.0f);
				break;
			case 4:
				ImGui::DragFloat("Constant", &pointLightCube->constant, 0.01f, 0.0f, 1.0f);
				break;
			case 5:
				ImGui::DragFloat("Linear", &pointLightCube->linear, 0.001f, 0.0f, 1.0f);
				break;
			case 6:
				ImGui::DragFloat("Quadratic", &pointLightCube->quadratic, 0.001f, 0.0f, 1.0f);
				break;
			case 7:
				ImGui::SliderFloat("Radius_", &radius, 0.1f, 150.0f);
				break;
			case 8:
				ImGui::SliderFloat3("Starting Position",(float*) &pointStartPosition, -50.0f, 400.0f);
			}
		}
	}

	void SetRootTransform(Transform* root)
	{
		rootTransform = root;
		dirLightCube->SetRootTransform(rootTransform);
		spotLightCubes[0]->SetRootTransform(rootTransform);
		spotLightCubes[1]->SetRootTransform(rootTransform);
		pointLightCube->SetRootTransform(rootTransform);
	}

	void DrawLights()
	{
		if (dirLight)
		{
			dirLightCube->SetProjectionMatrix(this->projectionMatrix);
			dirLightCube->SetViewMatrix(this->viewMatrix);
			dirLightCube->Draw();
		}

		if (spotLights[0])
		{
			spotLightCubes[0]->SetProjectionMatrix(this->projectionMatrix);
			spotLightCubes[0]->SetViewMatrix(this->viewMatrix);
			spotLightCubes[0]->Draw();
		}

		if (spotLights[1])
		{
			spotLightCubes[1]->SetProjectionMatrix(this->projectionMatrix);
			spotLightCubes[1]->SetViewMatrix(this->viewMatrix);
			spotLightCubes[1]->Draw();
		}

		if (pointLight)
		{
			if (pointLightFlying)
			{
				MovePointLight(radius);
			}
			pointLightCube->SetProjectionMatrix(this->projectionMatrix);
			pointLightCube->SetViewMatrix(this->viewMatrix);
			pointLightCube->Draw();
		}
	}

	void UpdateLights(Shaders houses, Shaders floor)
	{
		if (dirLight)
		{
			dirLightCube->UpdateShaderLight(floor);
			dirLightCube->UpdateShaderLight(houses);
		}

		if (spotLights[0])
		{
			spotLightCubes[0]->UpdateShaderLight(floor);
			spotLightCubes[0]->UpdateShaderLight(houses);
		}

		if (spotLights[1])
		{
			spotLightCubes[1]->UpdateShaderLight(floor, "spotLights[1]");
			spotLightCubes[1]->UpdateShaderLight(houses, "spotLights[1]");
		}

		if (pointLight)
		{
			pointLightCube->UpdateShaderLight(floor);
			pointLightCube->UpdateShaderLight(houses);
		}
	}

	void SetProjectionMatrix(glm::mat4 proj)
	{
		this->projectionMatrix = proj;
	}

	void SetViewMatrix(glm::mat4 view)
	{
		this->viewMatrix = view;
	}

	void SetHousesFloor(Shaders houses, Shaders floor)
	{
		this->housesShader = houses;
		this->floorShader = floor;
	}

	void MovePointLight(float radius = 10.0f)
	{
		if (oldRadius != radius)
		{
			oldRadius = radius;
			pointLightCube->transform.pos = pointStartPosition;
			pointLightCube->transform.eulerRot = glm::vec3(0.0f, 0.0f, 0.0f);
		}
		float x = cos(angle) * radius;
		float z = sin(angle) * radius;
		angle = angle >= 6.28 ? 0.0f : angle + 0.01f;

		pointLightCube->transform.ChangePosition(pointStartPosition + glm::vec3(x, 0.0f, z));
	}
};