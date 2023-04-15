#pragma once
#include "Include.h"

class Vertices
{
public:

	static std::vector<GLfloat> GetFloorVertices()
	{
		std::vector<GLfloat> vertices =
		{
			-1.0f, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			-1.0f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			 1.0f, 0.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

			-1.0f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			 1.0f, 0.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			 1.0f, 0.0f,  1.0f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f
		};

		return vertices;
	}

	static std::vector<GLfloat> GetHouseVertices()
	{
		std::vector<GLfloat> vertices =
		{
			//floor
			-1.0f, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
			-1.0f, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
			 1.0f, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f,

			-1.0f, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
			 1.0f, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
			 1.0f, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f,

			//front
			-1.0f, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 1.0f, 0.0f,  1.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, 1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			
			 1.0f, 0.0f,  1.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, 1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 1.0f, 1.0f,  1.0f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		
			 //back
			-1.0f, 0.0f, -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
			 1.0f, 0.0f, -1.0f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
			
			 1.0f, 0.0f, -1.0f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f,
			-1.0f, 1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
			 1.0f, 1.0f, -1.0f,  0.5f, 1.0f, 0.0f, 0.0f, -1.0f,

			 //left
		    -1.0f, 0.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		    -1.0f, 1.0f, -1.0f,  1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		    -1.0f, 0.0f,  1.0f,  0.5f, 0.0f, -1.0f, 0.0f, 0.0f,
		   
		    -1.0f, 1.0f, -1.0f,  1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		    -1.0f, 0.0f,  1.0f,  0.5f, 0.0f, -1.0f, 0.0f, 0.0f,
		    -1.0f, 1.0f,  1.0f,  0.5f, 1.0f, -1.0f, 0.0f, 0.0f,
		   
		    //right
		     1.0f, 0.0f, -1.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		     1.0f, 1.0f, -1.0f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f,
		     1.0f, 0.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

			 1.0f, 1.0f, -1.0f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f,
			 1.0f, 0.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			 1.0f, 1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f
		};

		return vertices;
	}

	static std::vector<GLfloat> GetRoofVertices()
	{
		std::vector<GLfloat> vertices =
		{
			-1.0f, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
			 1.0f, 0.0f, -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
			 0.0f, 1.0f,  0.0f,  0.5f, 1.0f, 0.0f, 0.0f, -1.0f,

			 1.0f, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, 0.0f,  1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 0.0f, 1.0f,  0.0f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,

			-1.0f, 0.0f,  1.0f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
			 0.0f, 1.0f,  0.0f,  0.5f, 1.0f, -1.0f, 0.0f, 0.0f,
			
			 1.0f, 0.0f, -1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			 1.0f, 0.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			 0.0f, 1.0f,  0.0f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f
		};

		return vertices;
	}

	static std::vector<GLfloat> GetCubeVertices()
	{
		std::vector<GLfloat> vertices =
		{
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f
		};

		return vertices;
	}

	static std::vector<GLfloat> GetCubeVerticesWithNormals()
	{
		std::vector<GLfloat> vertices =
		{
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};

		return vertices;
	}

	static std::vector<GLfloat> GetLineVertices()
	{
		std::vector<GLfloat> vertices =
		{
			0.0f, 0.0f, 0.0f,
			
			0.0f, 0.0f, 10.0f
		};

		return vertices;
	}

	static std::vector<GLfloat> GetSkyboxVertices()
	{
		std::vector<GLfloat> vertices =
		{
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

		return vertices;
	}

	static std::vector<GLfloat> GetWheelVertices()
	{
		std::vector<GLfloat> vertices;
		GLfloat x, y, z;
		GLfloat xn, yn, zn;

		for (float i = 0; i < 360; i += 1.0f)
		{
			if ((int)i % 30 == 0)
			{
				x = cos(glm::radians(i)) * 0.5f;
				y = sin(glm::radians(i)) * 0.5f;
				z = 0.0f;

				vertices.push_back(x / 3.0f);
				vertices.push_back(y / 3.0f);
				vertices.push_back(z);

				vertices.push_back(x * 2.0f);
				vertices.push_back(y * 2.0f);
				vertices.push_back(z);

				x = cos(glm::radians(i + 1.0f)) * 0.5f;
				y = sin(glm::radians(i + 1.0f)) * 0.5f;
				z = 0.0f;

				vertices.push_back(x / 3.0f);
				vertices.push_back(y / 3.0f);
				vertices.push_back(z);

				vertices.push_back(x * 2.0f);
				vertices.push_back(y * 2.0f);
				vertices.push_back(z);

				x = cos(glm::radians(i + 1.0f)) * 0.5f;
				y = sin(glm::radians(i + 1.0f)) * 0.5f;
				z = 1.0f;

				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);

				vertices.push_back(x * 2.0f);
				vertices.push_back(y * 2.0f);
				vertices.push_back(z);

				x = cos(glm::radians(i + 1.0f)) * 0.5f;
				y = sin(glm::radians(i + 1.0f)) * 0.5f;
				z = 0.0f;

				vertices.push_back(x / 3.0f);
				vertices.push_back(y / 3.0f);
				vertices.push_back(z);

				vertices.push_back(x * 2.0f);
				vertices.push_back(y * 2.0f);
				vertices.push_back(z);

				x = cos(glm::radians(i + 1.0f)) * 0.5f;
				y = sin(glm::radians(i + 1.0f)) * 0.5f;
				z = 1.0f;

				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);

				vertices.push_back(x * 2.0f);
				vertices.push_back(y * 2.0f);
				vertices.push_back(z);

				x = cos(glm::radians(i)) * 0.5f;
				y = sin(glm::radians(i)) * 0.5f;
				z = 0.0f;

				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);

				vertices.push_back(x * 2.0f);
				vertices.push_back(y * 2.0f);
				vertices.push_back(z);
				
			}
			x = cos(glm::radians(i)) * 0.5f;
			y = sin(glm::radians(i)) * 0.5f;
			z = 0.0f;
			
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
	
			vertices.push_back(x * 2.0f);
			vertices.push_back(y * 2.0f);
			vertices.push_back(z);

			x = cos(glm::radians(i + 1.0f)) * 0.5f;
			y = sin(glm::radians(i + 1.0f)) * 0.5f;
			z = 0.0f;
			
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			vertices.push_back(x * 2.0f);
			vertices.push_back(y * 2.0f);
			vertices.push_back(z);

			x = cos(glm::radians(i + 1.0f)) * 0.5f;
			y = sin(glm::radians(i + 1.0f)) * 0.5f;
			z = 1.0f;
			
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			vertices.push_back(x * 2.0f);
			vertices.push_back(y * 2.0f);
			vertices.push_back(z);

			x = cos(glm::radians(i)) * 0.5f;
			y = sin(glm::radians(i)) * 0.5f;
			z = 0.0f;

			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			vertices.push_back(x * 2.0f);
			vertices.push_back(y * 2.0f);
			vertices.push_back(z);

			x = cos(glm::radians(i + 1.0f)) * 0.5f;
			y = sin(glm::radians(i + 1.0f)) * 0.5f;
			z = 1.0f;

			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			vertices.push_back(x * 2.0f);
			vertices.push_back(y * 2.0f);
			vertices.push_back(z);

			x = cos(glm::radians(i)) * 0.5f;
			y = sin(glm::radians(i)) * 0.5f;
			z = 1.0f;

			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			vertices.push_back(x * 2.0f);
			vertices.push_back(y * 2.0f);
			vertices.push_back(z);
		}

		return vertices;
	}

	static std::vector<GLfloat> GetQuadVertices()
	{
		std::vector<GLfloat> vertices =
		{
			0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f
		};

		return vertices;
	}

};