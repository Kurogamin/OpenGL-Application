#pragma once

#include "Include.h"

class DirectionLine : public Object
{
private:
public:
	
	DirectionLine() : Object(Vertices::GetLineVertices())
	{
		this->shaders.loadShaders("res/shaders/lineVertex.vs", "res/shaders/lineFragment.fs");
		this->shaders.compilationStatus();
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);

		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), this->vertices.data(), GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
	
	void Draw(glm::mat4 parentMatrix)
	{
		shaders.useShaders();
		shaders.changeMat4s(this->transform.GetLocalModelMatrix() * parentMatrix, viewMatrix, projectionMatrix);
		shaders.changeVec4Uniform("materialColor", this->color);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindVertexArray(VAO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * vertices.size(), &vertices[0]);
		glDrawArrays(GL_LINES, 0, vertices.size() / 2);
	}

	void SetColor(glm::vec4 color)
	{
		this->color = color;
	}
};