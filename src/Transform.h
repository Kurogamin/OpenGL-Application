#pragma once
#include "Include.h"

struct Transform
{
	/*SPACE INFORMATION*/
	//Local space information
	glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
	glm::vec3 eulerRot = { 0.0f, 0.0f, 0.0f };
	glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
	glm::vec3 circlePos = { 0.0f, 0.0f, 0.0f };

	//Global space information concatenate in matrix
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	bool dirtyFlag = false;

	Transform()
	{
		pos = { 0.0f, 0.0f, 0.0f };
		eulerRot = { 0.0f, 0.0f, 0.0f };
		scale = { 1.0f, 1.0f, 1.0f };
		modelMatrix = glm::mat4(1.0f);
	}

	void ChangePosition(glm::vec3 newPos)
	{
		pos = newPos;
		dirtyFlag = true;
	}

	void ChangeRotation(glm::vec3 newRot)
	{
		eulerRot = newRot;
		dirtyFlag = true;
	}

	void ChangeScale(glm::vec3 newScale)
	{
		scale = newScale;
		dirtyFlag = true;
	}

	void AddPosition(glm::vec3 pos)
	{
		this->pos += pos;
		dirtyFlag = true;
	}

	void SetCirclePosition(glm::vec3 pos)
	{
		this->circlePos = pos;
		dirtyFlag = true;
	}

	void AddRotation(glm::vec3 rot)
	{
		this->eulerRot += rot;
		dirtyFlag = true;
	}

	void AddScale(glm::vec3 scale)
	{
		this->scale += scale;
		dirtyFlag = true;
	}

	void SetScale(float scale)
	{
		this->scale = glm::vec3(scale, scale, scale);
		dirtyFlag = true;
	}

	void MoveForward(float distance) //ONLY WORKS FOR LOCOMOTIVE
	{
		glm::vec3 forward = glm::vec3(-1.0f, 0.0f, 0.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 one = glm::mat4(1.0f);

		one = glm::rotate(one, glm::radians(eulerRot.y), up);

		glm::vec3 forwardRotated = (one * glm::vec4(forward, 1.0f));

		pos += forwardRotated * distance;
		dirtyFlag = true;
	}

	glm::vec3 GetScale()
	{
		return scale;
	}

	glm::vec3 GetDirection()
	{
		glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(eulerRot.x), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(eulerRot.y), glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 rot = rotY * rotX;

		return glm::vec3(rot * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	}

	glm::mat4 GetLocalModelMatrix()
	{
		if (dirtyFlag)
		{
			const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
				glm::radians(eulerRot.x),
				glm::vec3(1.0f, 0.0f, 0.0f));
			const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
				glm::radians(eulerRot.y),
				glm::vec3(0.0f, 1.0f, 0.0f));
			const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
				glm::radians(eulerRot.z),
				glm::vec3(0.0f, 0.0f, 1.0f));

			// Y * X * Z
			const glm::mat4 roationMatrix = transformY * transformX * transformZ;

			// translation * rotation * scale (also know as TRS matrix)
			this->modelMatrix = glm::translate(glm::mat4(1.0f), pos + circlePos) *
				roationMatrix *
				glm::scale(glm::mat4(1.0f), scale);
			return this->modelMatrix;
		}
		else
		{
			return this->modelMatrix;
		}
	}

	void EnableDirtyFlag()
	{
		this->dirtyFlag = true;
	}
};
