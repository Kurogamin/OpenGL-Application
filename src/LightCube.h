#pragma once

#include "Include.h"

class LightCube : public Object
{
private:
	void SetupShaders()
	{
		this->shaders.loadShaders("res/shaders/lightCubeVertex.vs", "res/shaders/lightCubeFragment.fs");
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
protected:
	Transform* rootTransform = nullptr;
public:
	glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	glm::vec3 diffuse = glm::vec3(0.4f, 0.04f, 0.04f);
	glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
	float constant = 1.0f;
	float linear = 0.045f;
	float quadratic = 0.0075f;
	float cutOff = 30.0f;
	float outerCutOff = 60.f;
	glm::mat4 projection, view, model;
	Transform transform;
	glm::mat4 modelMatrix;
	
	LightCube() : Object(Vertices::GetCubeVertices())
	{
		SetupShaders();
	}

	void Update(glm::mat4 projection, glm::mat4 view, glm::mat4 modelMatrix)
	{
		this->projection = projection;
		this->view = view;
		this->model = modelMatrix * transform.GetLocalModelMatrix();
	}

	void Draw()
	{
		Draw(model);
	}

	void Draw(glm::mat4 currentModel, glm::mat4 parentModel)
	{
		modelMatrix = currentModel * parentModel;
		Draw(modelMatrix);
	}

	void Draw(glm::mat4 model)
	{
		shaders.useShaders();
		shaders.changeMat4s(model, view, projection);
		shaders.changeVec4Uniform("materialColor", this->color);
		//shaders.changeMat4Uniform("rootMatrix", rootTransform->GetLocalModelMatrix());
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindVertexArray(VAO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * vertices.size(), &vertices[0]);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
	}

	void SetAmbient(glm::vec3 ambient)
	{
		this->ambient = ambient;
	}
	
	void SetDiffuse(glm::vec3 diffuse)
	{
		this->diffuse = diffuse;
	}
	
	void SetSpecular(glm::vec3 specular)
	{
		this->specular = specular;
	}
	
	void SetConstant(float constant)
	{
		this->constant = constant;
	}
	
	void SetLinear(float linear)
	{
		this->linear = linear;
	}
	
	void SetQuadratic(float quadratic)
	{
		this->quadratic = quadratic;
	}
	
	void SetCutOff(float cutOff)
	{
		this->cutOff = cutOff;
	}
	
	void SetOuterCutOff(float outerCutOff)
	{
		this->outerCutOff = outerCutOff;
	}

	void SetRootTransform(Transform* rootTransform)
	{
		this->rootTransform = rootTransform;
	}

	void SetColor(int r, int g, int b)
	{
		Object::SetColor(r, g, b);
		this->diffuse = glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f);
	}

	void SetColor(float r, float g, float b)
	{
		Object::SetColor(r, g, b);
		this->diffuse = glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f);
	}

	virtual void UpdateShaderLight(Shaders shader, std::string uniformName) = 0;
};