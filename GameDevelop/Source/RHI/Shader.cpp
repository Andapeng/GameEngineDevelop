#include "Shader.h"
#include <GLAD/glad.h>
#include <fstream>
#include <iostream>
Shader::Shader()
	:mVertexShader(0)
	,mFragmentShader(0)
	,mShaderProgram(0)
{

}

int Shader::LoadShaderString(const char* vertexShader, const char* fragmentShader)
{
	mVertexShader = glCreateShader(GL_VERTEX_SHADER);
	mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(mVertexShader, 1, &vertexShader, nullptr);
	glCompileShader(mVertexShader);

	glShaderSource(mFragmentShader, 1, &fragmentShader, nullptr);
	glCompileShader(mFragmentShader);

	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragmentShader);
	glLinkProgram(mShaderProgram);

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
		vertexShader += in.get();
	}
	in.clear();
	in.close();

	in.open(fragmentShaderPath);
	while (in)
	{
		fragmentShader += in.get();
	}
	in.clear();
	in.close();

//	std::cout << vertexShader << std::endl;
//	std::cout << fragmentShader << std::endl;
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
	glUniform1i(glGetUniformLocation(mShaderProgram, name), val);
	return 0;
}

int Shader::SetFloat(const char* name, float val)
{
	glUniform1f(glGetUniformLocation(mShaderProgram, name), val);
	return 0;
}

int Shader::SetVector3f(const char* name, Eigen::Vector3f vec)
{
	glUniform3f(glGetUniformLocation(mShaderProgram, name), vec(0), vec(1), vec(2));
	return 0;
}

int Shader::SetVector4f(const char* name, Eigen::Vector4f vec)
{
	glUniform4f(glGetUniformLocation(mShaderProgram, name), vec(0), vec(1), vec(2),vec(3));
	return 0;
}

int Shader::SetMatrix4f(const char* name, Eigen::Matrix4f mat)
{
	glUniformMatrix4fv(glGetUniformLocation(mShaderProgram, name), 1, GL_FALSE, mat.data());

	return 0;
}

