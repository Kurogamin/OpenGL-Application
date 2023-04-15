#pragma once
#include "Include.h"

class Shaders
{
private:
	const char* vertexShaderSource;
	const char* fragmentShaderSource;
	const char* geometryShaderSource;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint geometryShader = -11;
	GLuint shaderProgram;
public:
	Shaders()
	{
	}
	Shaders(std::string vertexShaderPath, std::string fragmentShaderPath)
	{
		loadShaders(vertexShaderPath, fragmentShaderPath);
		compilationStatus();
	}
	Shaders(std::string vertexShaderPath, std::string fragmentShaderPath, std::string geometryShaderPath)
	{
		loadShaders(vertexShaderPath, fragmentShaderPath, geometryShaderPath);
	}
	void shadersInit(const char* vertexShaderSource, const char* fragmentShaderSource)
	{
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	void shadersInit(const char* vertexShaderSource, const char* fragmentShaderSource, const char* geometryShaderSource)
	{
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &geometryShaderSource, NULL);
		glCompileShader(geometryShader);

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glAttachShader(shaderProgram, geometryShader);
		glLinkProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteShader(geometryShader);
	}
	void useShaders()
	{
		glUseProgram(shaderProgram);
	}
	void compilationStatus()
	{
		GLint shaderSuccess;
		GLint fragmentSuccess;
		GLint shaderProgramSuccess;

		GLchar infoLogShader[512];
		GLchar infoLogFragment[512];
		GLchar infoLogProgram[512];

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderSuccess);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentSuccess);
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderProgramSuccess);

		if (!shaderSuccess)
		{
			std::cout << "ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLogShader);
			std::cout << "VertexShader compilation failed" << infoLogShader << std::endl;
		}

		if (!fragmentSuccess)
		{
			std::cout << "ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLogFragment);
			std::cout << "FragmentShader compilation failed" << infoLogFragment << std::endl;
		}
		if (geometryShader != -11)
		{
			GLchar infoLogGeometry[512];
			GLint geometrySuccess;
			glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &geometrySuccess);
			if (!geometrySuccess)
			{
				std::cout << "ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
				glGetShaderInfoLog(vertexShader, 512, NULL, infoLogGeometry);
				std::cout << "GeometryShader compilation failed" << infoLogGeometry << std::endl;
			}
		}

		if (!shaderProgramSuccess)
		{
			std::cout << "ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLogProgram);
			std::cout << "ShaderProgram compilation failed" << infoLogProgram << std::endl;
		}
	}
	void changeColorUniform(std::string uniformName, GLfloat r, GLfloat g, GLfloat b, GLfloat alpha)
	{
		GLint uniformLocation = glGetUniformLocation(Shaders::shaderProgram, uniformName.c_str());
		glUniform4f(uniformLocation, r, g, b, alpha);
	}
	void changeMat4Uniform(std::string uniformName, glm::mat4 value)
	{
		GLint uniformLocation = glGetUniformLocation(Shaders::shaderProgram, uniformName.c_str());
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}
	void loadShaders(std::string vertexShaderPath, std::string fragmentShaderPath)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			vShaderFile.open(vertexShaderPath);
			fShaderFile.open(fragmentShaderPath);

			std::stringstream vShaderStream, fShaderStream, gShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		shadersInit(vShaderCode, fShaderCode);
	}
	void loadShaders(std::string vertexShaderPath, std::string fragmentShaderPath, std::string geometryShaderPath)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		std::ifstream gShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			vShaderFile.open(vertexShaderPath);
			fShaderFile.open(fragmentShaderPath);
			gShaderFile.open(geometryShaderPath);

			std::stringstream vShaderStream, fShaderStream, gShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			gShaderStream << gShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();
			gShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			geometryCode = gShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		const char* gShaderCode = geometryCode.c_str();

		shadersInit(vShaderCode, fShaderCode, gShaderCode);
	}
	void changeMat4s(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
	{
		changeMat4Uniform("model", model);
		changeMat4Uniform("view", view);
		changeMat4Uniform("proj", projection);
	}
	void changeVec4Uniform(std::string uniformName, glm::vec4 value)
	{
		GLint uniformLocation = glGetUniformLocation(Shaders::shaderProgram, uniformName.c_str());
		glUniform4fv(uniformLocation, 1, glm::value_ptr(value));
	}
	void changeVec3Uniform(std::string uniformName, glm::vec3 value)
	{
		GLint uniformLocation = glGetUniformLocation(Shaders::shaderProgram, uniformName.c_str());
		glUniform3fv(uniformLocation, 1, glm::value_ptr(value));
	}

	void changeFloatUniform(std::string uniformName, float value)
	{
		GLint uniformLocation = glGetUniformLocation(Shaders::shaderProgram, uniformName.c_str());
		glUniform1f(uniformLocation, value);
	}

	void changeIntUniform(std::string uniformName, int value)
	{
		GLint uniformLocation = glGetUniformLocation(Shaders::shaderProgram, uniformName.c_str());
		glUniform1i(uniformLocation, value);
	}
};