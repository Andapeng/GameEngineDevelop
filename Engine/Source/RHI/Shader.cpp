#include "Shader.h"
#include <GLAD/glad.h>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
Shader::Shader()
	:mShaderProgram(0)
{

}

Shader::~Shader()
{
}

int Shader::LoadShaderString(const char* vertexShader, const char* fragmentShader)
{
	unsigned int mVertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(mVertexShader, 1, &vertexShader, nullptr);
	glCompileShader(mVertexShader);
	checkCompileErrors(mVertexShader, "mVertex");

	glShaderSource(mFragmentShader, 1, &fragmentShader, nullptr);
	glCompileShader(mFragmentShader);
	checkCompileErrors(mFragmentShader, "mFragment");

	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragmentShader);
	glLinkProgram(mShaderProgram);
	checkCompileErrors(mShaderProgram, "mShaderProgram");

	glDeleteShader(mVertexShader);
	glDeleteShader(mFragmentShader);
	return 0;
}

int Shader::LoadShaderFile(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	std::string vertexShader;
	std::string fragmentShader;
	std::ifstream in;
	in.open(vertexShaderPath);
	while (in)
	{
		char ch = in.get();
		if (ch != EOF)
		{
			vertexShader += ch;
		}
	}
	in.clear();
	in.close();

	in.open(fragmentShaderPath);
	while (in)
	{
		char ch = in.get();
		if (ch != EOF)
		{
			fragmentShader += ch;
		}
	}
	in.clear();
	in.close();

	//std::cout << vertexShader << std::endl;
	//std::cout << fragmentShader << std::endl;
	LoadShaderString(vertexShader.data(), fragmentShader.data());

	return 0;
}

Shader* Shader::Use()
{
	glUseProgram(mShaderProgram);
	//std::cout << "Use shader :" << mShaderProgram << std::endl;
	return this;
}

int Shader::SetInt(const char* name, int val)
{
	this->Use();
	glUniform1i(glGetUniformLocation(mShaderProgram, name), val);
	return 0;
}

int Shader::SetFloat(const char* name, float val)
{
	this->Use();
	glUniform1f(glGetUniformLocation(mShaderProgram, name), val);
	return 0;
}

int Shader::SetVector2f(const char* name, Eigen::Vector2f vec)
{
	this->Use();
	glUniform2f(glGetUniformLocation(mShaderProgram, name), vec(0), vec(1));
	return 0;
}

int Shader::SetVector3f(const char* name, Eigen::Vector3f vec)
{
	this->Use();
	glUniform3f(glGetUniformLocation(mShaderProgram, name), vec(0), vec(1), vec(2));
	return 0;
}

int Shader::SetVector4f(const char* name, Eigen::Vector4f vec)
{
	this->Use();
	glUniform4f(glGetUniformLocation(mShaderProgram, name), vec(0), vec(1), vec(2),vec(3));
	return 0;
}

int Shader::SetMatrix4f(const char* name, Eigen::Matrix4f mat)
{
	this->Use();
	glUniformMatrix4fv(glGetUniformLocation(mShaderProgram, name), 1, GL_FALSE, mat.data());

	return 0;
}

void Shader::checkCompileErrors(unsigned int object, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
}