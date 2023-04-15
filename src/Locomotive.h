#pragma once

#include "Include.h"

class Locomotive
{
private:
	Shaders shaders;
	GLuint VAO, VBO;
	std::vector<Cube> cubes;
	std::vector<Cube> wheels;
	std::vector<Cube> pistons;
	Cube windows;
	glm::vec4 color = glm::vec4(1.f, 1.f, 1.f, 1.f);
	glm::mat4 view, projection, model;
	glm::vec3 cameraPos;
	float velocity = 0.0f;
	float rotation = 0.0f;
	float rotationY = 90.0f;
	float move = 0.0f;
	float circleRadius = 100.0f;
	float animationDelay = 3.0f;
	SpotLightCube* leftLight = nullptr;
	SpotLightCube* rightLight = nullptr;
	ParticleEmitter* particles = nullptr;
	bool isMoving = false;
	float moveStartTime = 0.0f;
	float smokeCooldown = 2.5f;
	bool presentation = false;

	void SetupCubes()
	{
		CreateMainBody();
		CreateWheels();
		CreateWindows();
		CreatePistons();
	}
	
	void CreatePistons()
	{
		CreateCube(glm::vec3(8.0f, 0.2f, 0.2f), glm::vec3(0.0f, -2.0f, 2.6f), 255, 255, 255, pistons);
		CreateCube(glm::vec3(0.5f, 0.4f, 0.4f), glm::vec3(-4.0f, -2.0f, 2.6f), 0, 255, 128, pistons);
		CreateCube(glm::vec3(0.5f, 0.4f, 0.4f), glm::vec3(4.0f, -2.0f, 2.6f), 0, 255, 128, pistons);
		
		CreateCube(glm::vec3(8.0f, 0.2f, 0.2f), glm::vec3(0.0f, -2.0f, -2.6f), 255, 255, 255, pistons);
		CreateCube(glm::vec3(0.5f, 0.4f, 0.4f), glm::vec3(-4.0f, -2.0f, -2.6f), 0, 255, 128, pistons);
		CreateCube(glm::vec3(0.5f, 0.4f, 0.4f), glm::vec3(4.0f, -2.0f, -2.6f), 0, 255, 128, pistons);
		
		CreateCube(glm::vec3(0.25f, 2.0f, 1.0f), glm::vec3(0.0f, -1.6f, -2.6f), 255, 255, 255, pistons);
		CreateCube(glm::vec3(0.25f, 2.0f, 1.0f), glm::vec3(0.0f, -1.6f, 2.6f), 255, 255, 255, pistons);
	}
		
	void CreateMainBody()
	{
		CreateCube(glm::vec3(10.0f, 4.0f, 4.0f), glm::vec3(0.0f), 128, 128, 128, cubes);
		CreateCube(glm::vec3(4.0f, 2.0f, 3.0f), glm::vec3(-7.0f, -1.0f, 0.0f), 0, 255, 0, cubes);
		CreateCube(glm::vec3(1.0f, 3.0f, 1.0f), glm::vec3(0.0f, 3.0f, 0.0f), 0, 255, 128, cubes);
	}

	void CreateWindows()
	{
		Cube win(Vertices::GetCubeVerticesWithNormals(), true);
		win.transform.ChangeScale(glm::vec3(2.0f, 2.0f, 3.0f));
		win.transform.AddPosition(glm::vec3(-6.0f, 1.0f, 0.0f));
		this->windows = win;
	}
	
	void CreateWheels()
	{
		CreateWheel(glm::vec3(2.0f, 2.0f, 0.5f), glm::vec3(4.0f, -2.0f, 2.0f), 0, 0, 255);
		CreateWheel(glm::vec3(2.0f, 2.0f, 0.5f), glm::vec3(4.0f, -2.0f, -2.5f), 255, 0, 0);
		CreateWheel(glm::vec3(2.0f, 2.0f, 0.5f), glm::vec3(-4.0f, -2.0f, 2.0f), 0, 0, 255);
		CreateWheel(glm::vec3(2.0f, 2.0f, 0.5f), glm::vec3(-4.0f, -2.0f, -2.5f), 255, 0, 0);
	}

	void CreateCube(glm::vec3 scale, glm::vec3 position, int r, int g, int b, std::vector<Cube>& collection)
	{
		Cube cube;
		cube.transform.ChangeScale(scale);
		cube.transform.AddPosition(position);
		cube.SetColor(r, g, b);
		collection.push_back(cube);
	}
	
	void CreateWheel(glm::vec3 scale, glm::vec3 position, int r, int g, int b)
	{
		Cube wheel(Vertices::GetWheelVertices());
		wheel.transform.ChangeScale(scale);
		wheel.transform.AddPosition(position);
		wheel.SetColor(r, g, b);
		wheels.push_back(wheel);

		Cube miniWheel(Vertices::GetWheelVertices());
		miniWheel.transform.ChangeScale(glm::vec3(scale.x / 3, scale.y / 3, scale.z));
		miniWheel.transform.AddPosition(position);
		miniWheel.SetColor(r, g, b);
		wheels.push_back(miniWheel);
	}

	void DrawWheels()
	{
		for (int i = 0; i < wheels.size(); i++)
		{
			wheels[i].Update(projection, view, transform.GetLocalModelMatrix());
			wheels[i].Draw(&this->shaders);
		}
	}

	void DrawMain()
	{
		for (int i = 0; i < cubes.size(); i++)
		{
			cubes[i].Update(projection, view, transform.GetLocalModelMatrix());
			cubes[i].Draw(&this->shaders);
		}
	}

	void DrawPistons()
	{
		for (int i = 0; i < pistons.size(); i++)
		{
			pistons[i].Update(projection, view, transform.GetLocalModelMatrix());
			pistons[i].Draw(&this->shaders);
		}
	}

	void DrawWindows()
	{
		windows.Update(projection, view, transform.GetLocalModelMatrix());
		windows.Draw();
	}

	void DrawLights()
	{
		leftLight->Update(projection, view, transform.GetLocalModelMatrix());
		rightLight->Update(projection, view, transform.GetLocalModelMatrix());

		Transform newTransform;
		newTransform.eulerRot = this->transform.eulerRot;
		newTransform.AddRotation(glm::vec3(0.0f, -90.0f, 0.0f));
		glm::vec3 direction = newTransform.GetDirection();

		this->leftLight->SetDirection(direction);
		this->rightLight->SetDirection(direction);
		
		leftLight->Draw();
		rightLight->Draw();
	}

	void DrawParticles()
	{
		float dt = 1000.0f / ImGui::GetIO().Framerate;
		particles->UpdateShader(projection, view, transform.GetLocalModelMatrix());
		particles->DrawParticles(dt, this->cameraPos);
	}

	void RotateWheels()
	{
		for (int i = 0; i < wheels.size(); i++)
		{
			wheels[i].transform.AddRotation(glm::vec3(0.0f, 0.0f, velocity / animationDelay));
		}
	}

	void MovePistons()
	{
		float x, y, z;
		for (int i = 0; i < (pistons.size() - 2) / 2; i++)
		{
			x = cos(glm::radians((float)rotation)) * 0.5f;
			y = sin(glm::radians((float)rotation)) * 0.5f;
			z = 0.0f;
			pistons[i].transform.SetCirclePosition(glm::vec3(x, y, z));
			pistons[pistons.size() - 3 - i].transform.SetCirclePosition(glm::vec3(x, y, z));
		}
		rotation += velocity / animationDelay;
	}

	void UpdateMovements()
	{
		RotateWheels();
		MovePistons();
		if (!presentation)
		{
			MoveLocomotive();
		}
	}

	void MoveLocomotive()
	{
		if (velocity != 0.0f)
		{
			this->transform.MoveForward(velocity / 100.0f);
			if (!isMoving)
			{
				isMoving = true;
				moveStartTime = glfwGetTime();
			}
			if (moveStartTime + smokeCooldown - glfwGetTime() < 0)
			{
				this->particles->AddParticlesToSpawn(2000);
				moveStartTime = glfwGetTime();
				float random = -0.5f + (rand() % 100) / 100.0f;
				if (smokeCooldown < 2.0f) smokeCooldown += random;
				else smokeCooldown = smokeCooldown -= random;
			}
			
		}
		else
		{
			if (isMoving) isMoving = false;
		}
	}

	void RotateLocomotive()
	{
		this->transform.AddRotation(glm::vec3(0.0f, -(velocity / 30.0f), 0.0f));
	}

public:
	Transform transform;
	Locomotive()
	{
		//this->velocity = 22.0f;
		this->particles = new ParticleEmitter(1000);
		//this->particles->transform.ChangePosition(glm::vec3(0.0f, 0.0f, 0.0f));
		shaders = Shaders("res/shaders/loco.vs", "res/shaders/loco.fs");
		transform.ChangePosition(glm::vec3(5.0f, 5.0f, 5.0f));
		SetupCubes();
	}

	void Draw()
	{
		UpdateMovements();
		DrawMain();
		DrawPistons();
		DrawWheels();
		DrawWindows();
		DrawLights();
		//DrawParticles();
	}

	void SetProjectionMatrix(glm::mat4 projection)
	{
		this->projection = projection;
	}

	void SetViewMatrix(glm::mat4 view)
	{ 
		this->view = view;
	}

	void SetLights(SpotLightCube* left, SpotLightCube* right)
	{
		this->leftLight = left;
		this->rightLight = right;
		
		this->leftLight->transform.ChangeScale(glm::vec3(0.3f, 0.3f, 0.3f));
		this->leftLight->transform.ChangePosition(glm::vec3(-9.0f, -0.5f, 1.0f));
		this->rightLight->transform.ChangeScale(glm::vec3(0.3f, 0.3f, 0.3f));
		this->rightLight->transform.ChangePosition(glm::vec3(-9.0f, -0.5f, -1.0f));
		
		this->leftLight->SetDirection(this->transform.GetDirection());
		this->rightLight->SetDirection(this->transform.GetDirection());
	}

	void SetColor(int r, int g, int b)
	{
		this->color = glm::vec4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
		for (int i = 0; i < cubes.size(); i++)
		{
			//cubes[i].SetColor(this->color);
		}
	}

	Shaders GetShaders()
	{
		return this->shaders;
	}
	
	Cube* GetWindows()
	{
		return &this->windows;
	}

	void SetCameraPos(glm::vec3 cameraPos)
	{
		this->cameraPos = cameraPos;
		this->windows.SetCameraPos(cameraPos);
	}

	void Gui()
	{
		if (ImGui::CollapsingHeader("Locomotive", 26))
		{
			if (!presentation)
				presentation = true;
			
			ImGui::SliderFloat("Velocity", &this->velocity, 0.0f, 100.0f);
			if (ImGui::CollapsingHeader("Height", 26))
			{
				ImGui::SliderFloat("Locomotive Y", (float*)&this->transform.pos.y, 0.0f, 10.0f);
			}
			if (ImGui::CollapsingHeader("Windows", 26))
			{
				this->windows.Gui();
			}
			if (ImGui::Button("Emit smoke"))
			{
				this->particles->AddParticlesToSpawn(2000);
			}
		}
		else
		{
			if (presentation)
			{
				presentation = false;
				this->velocity = 0.0f;
			}
		}
	}

	void ProcessKeyboard(Camera_Movement direction)
	{
		if (direction == FORWARD)
		{
			this->velocity = this->velocity + 0.1f > 50.0f ? 50.0f : this->velocity + 0.1f;
		}
		if (direction == BACKWARD)
		{
			this->velocity = this->velocity - 0.1f < -50.0f ? -50.0f : this->velocity - 0.1f;
		}
		if (direction == LEFT)
		{
			this->transform.AddRotation(glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (direction == RIGHT)
		{
			this->transform.AddRotation(glm::vec3(0.0f, -1.0f, 0.0f));	
		}
		if (direction == SPACE)
		{
			this->velocity = 0.0f;
		}
	}

	glm::mat4 GetModelMatrix()
	{
		return this->transform.GetLocalModelMatrix();
	}

	void SetParticleEmitter(ParticleEmitter* emitter)
	{
		this->particles = emitter;
	}
};