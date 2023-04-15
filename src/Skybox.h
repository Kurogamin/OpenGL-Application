#pragma once

#include "Include.h"

class Skybox
{
private:
    std::vector<std::string> faces;
    std::vector<GLfloat> vertices;
    glm::mat4 projection;
    glm::mat4 view;
    GLuint skyboxId, VBO, VAO;
    Shaders shaders;

	void Initialize()
    {
        this->skyboxId = loadCubemap(this->faces);
        this->vertices = Vertices::GetSkyboxVertices();
        this->shaders = Shaders("res/shaders/skyboxVertex.vs", "res/shaders/skyboxFragment.fs");
		
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
		
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), this->vertices.data(), GL_STATIC_DRAW);
		
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    }
	
public:
    Skybox(std::vector<std::string> newFaces)
    {
        this->faces = newFaces;
        Initialize();
    }
	
    Skybox()
    {
		faces.push_back("res/textures/right.jpg");
		faces.push_back("res/textures/left.jpg");
		faces.push_back("res/textures/top.jpg");
		faces.push_back("res/textures/bottom.jpg");
		faces.push_back("res/textures/front.jpg");
		faces.push_back("res/textures/back.jpg");
        Initialize();
    }
	
    GLuint loadCubemap(std::vector<std::string> faces)
    {
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(false);
        for (unsigned int i = 0; i < faces.size(); i++)
        {
            unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                );
                stbi_image_free(data);
            }
            else
            {
                std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
                stbi_image_free(data);
            }
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        return textureID;
    }
	
    void Draw()
    {
        glDepthMask(GL_FALSE);
        shaders.useShaders();
        shaders.changeMat4Uniform("view", this->view);
        shaders.changeMat4Uniform("projection", this->projection);
        // skybox cube
        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxId);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthMask(GL_TRUE);
    }

	void SetViewMatrix(glm::mat3 newView)
	{
		this->view = newView;
	}

	void SetProjectionMatrix(glm::mat4 projection)
	{
		this->projection = projection;
	}
};