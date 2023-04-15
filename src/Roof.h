#pragma once
#include "Include.h"

class Roof : public Object
{
private:
public:
	Material material;
	Roof(std::vector<GLfloat> newVertices) : Object(newVertices)
	{
		this->shaders.loadShaders("res/shaders/housesVertex.vs", "res/shaders/housesFragment.fs");
		this->shaders.compilationStatus();
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);

		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), this->vertices.data(), GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}

	Roof() : Roof(Vertices::GetRoofVertices())
	{
		this->texture = Utilities::LoadTexture("res/textures/roof.jpg");
	}

	void Draw(glm::mat4 parentModelMatrix)
	{
		shaders.useShaders();
		shaders.changeMat4s(parentModelMatrix * transform.GetLocalModelMatrix(), viewMatrix, projectionMatrix);
		shaders.changeVec4Uniform("materialColor", this->color);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindVertexArray(VAO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * vertices.size(), &vertices[0]);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 5);
	}

	void SetMaterial(int r, int g, int b, glm::vec3 specular, float shininess)
	{
		this->material = Material(r, g, b, specular, shininess);
	}
};