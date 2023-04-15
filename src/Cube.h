#pragma once

#include "Include.h"

class Cube
{
private:
	Shaders shaders;
	GLuint VBO, VAO;
	glm::vec4 color = glm::vec4(1.f, 1.f, 1.f, 1.f);
	std::vector<GLfloat> vertices;
	glm::mat4 view, projection, model;
	glm::vec3 cameraPos;
	bool refractive = 0;
	float ratio = 1.0f;
	int option = -1;
	bool seeThrough = false;

	void Initialize()
	{
		LoadShaders();
		SetupBuffers();
	}

	void LoadShaders()
	{
		shaders = Shaders("res/shaders/cube.vs", "res/shaders/cube.fs");
	}

	void SetupBuffers()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);


		glBindVertexArray(0);
	}
public:
	Transform transform;

	Cube(std::vector<GLfloat> vertices, bool refractive)
	{
		this->refractive = (int) refractive;
		this->vertices = vertices;
		Initialize();
		seeThrough = true;
	}

	Cube(std::vector<GLfloat> vertices)
	{
		this->vertices = vertices;
		SetupBuffers();
	}

	Cube()
	{
		this->vertices = Vertices::GetCubeVerticesWithNormals();
		SetupBuffers();
	}
	
	void Draw(Shaders* shaders)
	{
		shaders->useShaders();

		shaders->changeMat4Uniform("model", model);
		shaders->changeMat4Uniform("view", view);
		shaders->changeMat4Uniform("proj", projection);
		shaders->changeVec4Uniform("materialColor", this->color);

		if (seeThrough)
		{
			shaders->changeIntUniform("skybox", 0);
			shaders->changeVec3Uniform("cameraPos", cameraPos);
			float actualRatio = 1.0f / ratio;
			shaders->changeFloatUniform("ratio", actualRatio);
			if (refractive)
			{
				shaders->changeIntUniform("refraction", 1);
			}
			else
			{
				shaders->changeIntUniform("refraction", 0);
			}
		}

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 6);
		glBindVertexArray(0);
	}
	
	void Draw()
	{
		Draw(&this->shaders);
	}

	void SetViewMatrix(glm::mat4 viewMatrix)
	{
		this->view = viewMatrix;
	}

	void SetProjectionMatrix(glm::mat4 projectionMatrix)
	{
		this->projection = projectionMatrix;
	}

	void SetCameraPos(glm::vec3 cameraPos)
	{
		this->cameraPos = cameraPos;
	}

	void SetColor(int r, int g, int b)
	{
		glm::vec4 newColor = glm::vec4(r / 255.f, g / 255.f, b / 255.f, 1.f);
		this->color = newColor;
	}

	void SetColor(glm::vec4 color)
	{
		this->color = color;
	}

	void Gui()
	{
		//ImGui::DragInt("Refractive Slider", (int*)&refractive, 1, 0, 1);
		if (ImGui::Button("Refract/Reflect"))
		{
			refractive = !refractive;
		}
		if (refractive) ImGui::DragFloat("Ratio Slider", (float*)&ratio, 0.01f, 1.0f, 3.0f);
	}

	void Update(glm::mat4 projection, glm::mat4 view, glm::mat4 modelMatrix)
	{
		this->projection = projection;
		this->view = view;
		this->model = modelMatrix * transform.GetLocalModelMatrix();
	}
};