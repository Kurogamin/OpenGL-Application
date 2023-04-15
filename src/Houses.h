#pragma once
#include "Include.h"


class Houses
{
	House baseHouse;
	Roof baseRoof;
	int houseCount = 0;
	glm::mat4 baseHouseMatrix;
	glm::mat4 baseRoofMatrix;
	std::vector<Transform> houseTransforms;
	std::vector<Transform> roofTransforms;
	std::vector<glm::mat4> houseModels;
	std::vector<glm::mat4> roofModels;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	Shaders roofShaders;
	Shaders housesShaders;
	GLuint housesVBO, roofsVBO, housesVAO, roofsVAO;
	GLuint houseModelsVBO, roofModelsVBO;
	float distanceBetweenHouses = 3.0f;
	float housesScale = 1.0f;
	bool shadersLoaded = false;
	bool transformsCalculated = false;
	glm::vec4 lightColor;

	void CalculateTransforms()
	{
		houseTransforms.clear();
		roofTransforms.clear();
		houseModels.clear();
		roofModels.clear();
		
		
		Transform currentHouse;
		Transform currentRoof;
		int housesInARow = 1;
		
		while (housesInARow * housesInARow < houseCount)
		{
			housesInARow++;
		}

		distanceBetweenHouses = 3.0f;

		housesScale = 0.5f;
		baseHouse.transform.ChangeScale(glm::vec3(housesScale, housesScale, housesScale));

		float leftPosition = baseHouse.transform.pos.x;


		houseTransforms.push_back(baseHouse.transform);
		roofTransforms.push_back(baseRoof.transform);

		houseModels.push_back(houseTransforms[0].GetLocalModelMatrix());
		roofModels.push_back(houseTransforms[0].GetLocalModelMatrix() * roofTransforms[0].GetLocalModelMatrix());

		for (int i = 1; i < houseCount; i++)
		{
			if (i % housesInARow != 0)
			{
				currentHouse = houseTransforms[i - 1];
				currentHouse.AddPosition(glm::vec3(distanceBetweenHouses, 0.0f, 0.0f));
				houseTransforms.push_back(currentHouse);
			}
			else
			{
				currentHouse = houseTransforms[i - 1];
				currentHouse.pos.x = leftPosition;
				currentHouse.AddPosition(glm::vec3(0.0f, 0.0f, distanceBetweenHouses));
				houseTransforms.push_back(currentHouse);
			}			

			currentRoof = roofTransforms[i - 1];
			roofTransforms.push_back(currentRoof);

			houseModels.push_back(houseTransforms[i].GetLocalModelMatrix());
			roofModels.push_back(houseTransforms[i].GetLocalModelMatrix() * roofTransforms[i].GetLocalModelMatrix());
		}

		transformsCalculated = true;
	}

	void LoadShaders()
	{
		std::vector<GLfloat> houseVertices = baseHouse.GetVertices();
		std::vector<GLfloat> roofVertices = baseRoof.GetVertices();
		
		this->housesShaders.loadShaders("res/shaders/housesVertex.vs", "res/shaders/housesFragment.fs");
		this->housesShaders.compilationStatus();
		this->roofShaders.loadShaders("res/shaders/housesVertex.vs", "res/shaders/housesFragment.fs");
		this->roofShaders.compilationStatus();
			
		glGenVertexArrays(1, &this->housesVAO);
		glGenVertexArrays(1, &this->roofsVAO);
		glGenBuffers(1, &this->housesVBO);
		glGenBuffers(1, &this->houseModelsVBO);
		glGenBuffers(1, &this->roofsVBO);
		glGenBuffers(1, &this->roofModelsVBO);

		SetupVAO(this->houseModelsVBO, this->houseModels, this->housesVBO, houseVertices, this->housesVAO);
		SetupVAO(this->roofModelsVBO, this->roofModels, this->roofsVBO, roofVertices, this->roofsVAO);

		shadersLoaded = true;
	}

	void SetupVAO(GLuint modelsVBO, std::vector<glm::mat4> models, GLuint verticesVBO, std::vector<GLfloat> vertices, GLuint VAO)
	{
		glBindBuffer(GL_ARRAY_BUFFER, modelsVBO);
		glBufferData(GL_ARRAY_BUFFER, models.size() * sizeof(glm::mat4), models.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

		// position attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
		// texture coord attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		// normals
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, modelsVBO);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}

	
public:
	Transform root;

	Houses()
	{
		baseHouse = House();
		baseRoof = Roof();
		baseHouse.SetColor(64, 0, 0);
		baseRoof.SetColor(0, 64, 0);
		baseHouse.SetMaterial(255, 255, 255, glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
		baseHouse.transform.AddPosition(glm::vec3(-3.0f, 0.0f, -3.0f));
		baseRoof.transform.AddPosition(glm::vec3(0.0f, 1.0f, 0.0f));
		baseHouse.SetMaterial(255, 255, 255, glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
		baseHouseMatrix = baseHouse.transform.GetLocalModelMatrix();
		baseRoofMatrix = baseHouseMatrix * baseRoof.transform.GetLocalModelMatrix();
	}

	void DrawHouses()
	{
		if (!transformsCalculated)
		{
			CalculateTransforms();
		}
		
		if (!shadersLoaded)
		{
			LoadShaders();
		}

		this->housesShaders.useShaders();
		this->housesShaders.changeMat4Uniform("view", this->viewMatrix);
		this->housesShaders.changeMat4Uniform("proj", this->projectionMatrix);
		this->housesShaders.changeVec4Uniform("lightColor_", this->lightColor);
		this->housesShaders.changeMat4Uniform("rootMatrix", Setup::GetRootTransform()->GetLocalModelMatrix());
		
		
		DrawWalls();
		DrawRoofs();
	}
	
	Transform& GetBaseHouseTransform()
	{
		return baseHouse.transform;
	}

	Shaders GetShaders()
	{
		return this->housesShaders;
	}

	void AddPositionToHouseIndex(int houseIndex, glm::vec3 position)
	{
		houseTransforms[houseIndex].AddPosition(position);
		roofModels[houseIndex] = houseTransforms[houseIndex].GetLocalModelMatrix() * roofTransforms[houseIndex].GetLocalModelMatrix();
		glBindBuffer(GL_ARRAY_BUFFER, this->houseModelsVBO);
		glBufferSubData(GL_ARRAY_BUFFER, houseIndex * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(houseModels[houseIndex]));

	}

	void AddPositionToRoofIndex(int roofIndex, glm::vec3 position)
	{
		roofTransforms[roofIndex].AddPosition(position);
		roofModels[roofIndex] = houseTransforms[roofIndex].GetLocalModelMatrix() * roofTransforms[roofIndex].GetLocalModelMatrix();
		glBindBuffer(GL_ARRAY_BUFFER, this->roofModelsVBO);
		glBufferSubData(GL_ARRAY_BUFFER, roofIndex * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(roofModels[roofIndex]));
	}

	void SetHouseCount(int count)
	{
		houseCount = count;
		std::vector<Transform> houseTransforms = std::vector<Transform>(houseCount);
		std::vector<Transform> roofTransforms = std::vector<Transform>(houseCount);
		houseModels = std::vector<glm::mat4>(houseCount);
		roofModels = std::vector<glm::mat4>(houseCount);
	}

	void SetProjectionMatrix(glm::mat4 proj)
	{
		this->projectionMatrix = proj;
		baseHouse.SetProjectionMatrix(proj);
		baseRoof.SetProjectionMatrix(proj);
	}
	
	void SetViewMatrix(glm::mat4 view)
	{
		this->viewMatrix = view;
		baseHouse.SetViewMatrix(view);
		baseRoof.SetViewMatrix(view);
	}

	void SetLightColor(int r, int g, int b)
	{
		this->lightColor = glm::vec4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
	}

	void SetLightPosition(glm::vec3 lightPos)
	{
		this->housesShaders.useShaders();
		this->housesShaders.changeVec3Uniform("light.position", lightPos);
	}

	void SetCameraPosition(glm::vec3 camPos)
	{
		this->housesShaders.useShaders();
		this->housesShaders.changeVec3Uniform("viewPos", camPos);
	}

	void DrawWalls()
	{
		housesShaders.changeVec4Uniform("materialColor", baseHouse.GetColor());
		baseHouse.material.UpdateShaderMaterial(this->housesShaders);
		Utilities::ChangeTexture(baseHouse.GetTexture(), 3);
		glBindVertexArray(this->housesVAO);
		glDrawArraysInstanced(GL_TRIANGLES, 0, baseHouse.GetVertices().size() / 5, houseCount);
	}

	void DrawRoofs()
	{
		housesShaders.changeVec4Uniform("materialColor", baseRoof.GetColor());
		baseHouse.material.UpdateShaderMaterial(this->housesShaders);
		Utilities::ChangeTexture(baseRoof.GetTexture(), 3);
		glBindVertexArray(this->roofsVAO);
		glDrawArraysInstanced(GL_TRIANGLES, 0, baseRoof.GetVertices().size() / 5, houseCount);
	}
};