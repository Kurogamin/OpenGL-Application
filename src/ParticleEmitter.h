#pragma once

#include "Include.h"

class ParticleEmitter
{
private:
	Shaders shader;
	glm::mat4 proj, view, model;
	std::vector<GLfloat> vertices;
	int particlesToSpawn = 0;
	int spawned = 0;

	struct Particle
	{
		glm::vec3 position;
		float lifetime;
		float cameraDistance;

		bool operator<(Particle& that)
		{
			// Sort in reverse order : far particles drawn first.
			return this->cameraDistance > that.cameraDistance;
		}
	};
	std::vector<Particle> particles;
	std::vector<GLfloat> positions;

	GLuint VBO, VAO, posBuffer;

	void Update(float dt, glm::vec3 cameraPos)
	{
		srand(time(NULL));
		for (GLuint i = 0; i < this->particles.size(); ++i)
		{
			this->particles[i].cameraDistance = glm::length(this->particles[i].position - cameraPos);
			this->particles[i].lifetime -= dt;

			if (this->particles[i].lifetime <= 0.0f && particlesToSpawn > 0 && spawned < 12)
			{
				glm::vec4 position = glm::vec4(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
				glm::vec4 newPos = this->model * position;
				glm::vec3 finalPos = glm::vec3(newPos.x, newPos.y, newPos.z);
				this->particles[i].position = finalPos;
				this->particles[i].lifetime = 500.0f + rand() % 800;
				
				//std::cout << particlesToSpawn-- << std::endl;
				particlesToSpawn--;
				spawned++;
			}
			else if (this->particles[i].lifetime > 0.0f)
			{
				float x = ((rand() % 200) - 100) / 20000.f;
				float y = 0.001f + rand() % 100 / 10000.f;
				float z = ((rand() % 200) - 100) / 20000.f;

				this->particles[i].position += glm::vec3(dt * x, dt * y, dt * z);
			}

			this->positions[i * 4 + 0] = this->particles[i].position.x;
			this->positions[i * 4 + 1] = this->particles[i].position.y;
			this->positions[i * 4 + 2] = this->particles[i].position.z;
			this->positions[i * 4 + 3] = this->particles[i].lifetime;
			
		}
		//if (particlesToSpawn > 0)
			//std::cout << particlesToSpawn << std::endl;
		spawned = 0;
		std::sort(this->particles.begin(), this->particles.end());
	}

	void Draw()
	{

		glBindVertexArray(VAO);
		
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(4);

		// update the position buffer
		glBindBuffer(GL_ARRAY_BUFFER, this->posBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, this->particles.size() * 4 * sizeof(float), this->positions.data());

		// vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		// position buffer
		glBindBuffer(GL_ARRAY_BUFFER, this->posBuffer);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
		glVertexAttribDivisor(4, 1);

		// draw triangles
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, this->particles.size());

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(4);

		glBindVertexArray(0);
	}

	void InitShaders()
	{
		this->shader = Shaders("res/shaders/particle.vs", "res/shaders/particle.fs");
		SetupBuffers();
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

	ParticleEmitter()
	{
		
	}
	
	ParticleEmitter(int count)
	{
		this->vertices = Vertices::GetQuadVertices();
		InitShaders();

		this->particles.resize(count);
		this->positions.resize(count * 4);
		srand(time(NULL));
		
		glBindVertexArray(VAO);
		// create a vertex and position buffer
		glGenBuffers(1, &this->VBO);
		glGenBuffers(1, &this->posBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

		// fill the position buffer
		glBindBuffer(GL_ARRAY_BUFFER, this->posBuffer);
		glBufferData(GL_ARRAY_BUFFER, this->particles.size() * 4 * sizeof(float), this->positions.data(), GL_DYNAMIC_DRAW);

		glBindVertexArray(0);
	}

	~ParticleEmitter()
	{
		glDeleteBuffers(1, &this->VBO);
		glDeleteBuffers(1, &this->posBuffer);
	}

	void UpdateShader(glm::mat4 projection, glm::mat4 view, glm::mat4 modelMatrix)
	{
		this->proj = projection;
		this->view = view;
		this->model = modelMatrix * transform.GetLocalModelMatrix();
	}

	void DrawParticles(float dt, glm::vec3 cameraPos)
	{
		Update(dt, cameraPos);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		
		this->shader.useShaders();
		this->shader.changeMat4s(model, view, proj);
		this->shader.changeFloatUniform("particleSize", 0.5f);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Draw();
	}

	void AddParticlesToSpawn(int count)
	{
		this->particlesToSpawn += count;
		if (this->particlesToSpawn > 5000)
			this->particlesToSpawn = 5000;
	}

	void Gui()
	{
		if (ImGui::CollapsingHeader("Smoke", 26))
		{
			if (ImGui::Button("Emit smoke"))
			{
				AddParticlesToSpawn(10000);
			}
		}
	}
};