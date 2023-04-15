#pragma once
#include "Include.h"

class Object
{
protected:
	Shaders shaders;
	GLuint VBO, VAO, texture;
	glm::vec4 color = glm::vec4(1.f, 1.f, 1.f, 1.f);
	std::vector<Object*> children;
	std::vector<GLfloat> vertices;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::vec4 lightColor;
public:
	Transform transform;

	Object(std::vector<GLfloat> newVertices)
	{
		this->vertices = newVertices;
	}

	~Object()
	{
	}

	void SetScale(float scale)
	{
		transform.SetScale(scale);
	}

	void SetColor(int r, int g, int b)
	{
		glm::vec4 newColor = glm::vec4(r / 255.f, g / 255.f, b / 255.f, 1.f);
		this->color = newColor;
	}

	void SetColor(float r, float g, float b)
	{
		glm::vec4 newColor = glm::vec4(r / 255.f, g / 255.f, b / 255.f, 1.f);
		this->color = newColor;
	}

	void SetTexture(GLuint texture)
	{
		this->texture = texture;
	}

	void SetProjectionMatrix(glm::mat4 proj)
	{
		this->projectionMatrix = proj;
	}

	void SetViewMatrix(glm::mat4 view)
	{
		this->viewMatrix = view;
	}

	Shaders GetShaders()
	{
		return this->shaders;
	}

	std::vector<GLfloat> GetVertices()
	{
		std::vector<GLfloat> newVertices(this->vertices);
		return newVertices;
	}

	glm::vec4 GetColor()
	{
		return this->color;
	}

	GLuint GetTexture()
	{
		return this->texture;
	}

	void SetLightColor(int r, int g, int b)
	{
		this->lightColor = glm::vec4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
	}

	void SetLightPosition(glm::vec3 lightPos)
	{
		this->shaders.useShaders();
		this->shaders.changeVec3Uniform("light.position", lightPos);
	}

	void SetCameraPosition(glm::vec3 camPos)
	{
		this->shaders.useShaders();
		this->shaders.changeVec3Uniform("viewPos", camPos);
	}

	virtual void Draw(glm::mat4 modelMatrix) = 0;
};
