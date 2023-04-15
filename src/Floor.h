#pragma once
#include "Include.h"

class Floor : public Object
{
private:
	Material material;
	GLuint texture;
public:
	Floor(std::vector<GLfloat> newVertices) : Object(newVertices)
	{
		this->shaders.loadShaders("res/shaders/vertex.vs", "res/shaders/fragment.fs");
		this->shaders.compilationStatus();
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);

		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), this->vertices.data(), GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		// normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
	}

	Floor() : Floor(Vertices::GetFloorVertices())
	{
		this->texture = Utilities::LoadTexture("res/textures/white.jpg");
		this->material = Material(glm::vec3(0.5f), glm::vec3(0.5f), glm::vec3(0.5f), 32.0f);
	}

	void Draw()
	{
		shaders.useShaders();
		shaders.changeMat4s(transform.GetLocalModelMatrix(), viewMatrix, projectionMatrix);
		shaders.changeVec4Uniform("materialColor", this->color);
		material.UpdateShaderMaterial(this->shaders);
		//shaders.changeMat4Uniform("rootMatrix", Setup::GetRootTransform()->GetLocalModelMatrix());
		shaders.changeMat4Uniform("rootMatrix", glm::mat4(1.0f));
		this->shaders.changeVec4Uniform("lightColor_", this->lightColor);
		Utilities::ChangeTexture(this->texture, 5);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindVertexArray(VAO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * vertices.size(), &vertices[0]);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 8);
	}

	void Draw(glm::mat4 parentModelMatrix)
	{
		shaders.useShaders();
		shaders.changeMat4s(parentModelMatrix * transform.GetLocalModelMatrix(), viewMatrix, projectionMatrix);
		shaders.changeVec4Uniform("materialColor", this->color);
		this->shaders.changeVec4Uniform("lightColor_", this->lightColor);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindVertexArray(VAO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * vertices.size(), &vertices[0]);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 8);
	}
};
