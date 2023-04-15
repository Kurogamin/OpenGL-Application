#pragma once
#include "Include.h"

class House : public Object
{
private:
public:
	Material material;
	House(std::vector<GLfloat> newVertices) : Object(newVertices)
	{
		this->shaders.loadShaders("res/shaders/vertex.vs", "res/shaders/fragment.fs");
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

	House() : House(Vertices::GetHouseVertices())
	{
		this->texture = Utilities::LoadTexture("res/textures/house.jpg");
	}

	void Draw(glm::mat4 modelMatrix)
	{
		shaders.useShaders();
		shaders.changeMat4s(modelMatrix, viewMatrix, projectionMatrix);
		shaders.changeVec4Uniform("materialColor", this->color);
		Utilities::ChangeTexture(this->texture, 3);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindVertexArray(VAO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * vertices.size(), &vertices[0]);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 5);
	}

	void Draw()
	{
		Draw(transform.GetLocalModelMatrix());
	}

	void SetMaterial(int r, int g, int b, glm::vec3 specular, float shininess)
	{
		this->material = Material(r, g, b, specular, shininess);
	}
};