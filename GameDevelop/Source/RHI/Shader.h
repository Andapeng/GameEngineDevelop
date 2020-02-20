#pragma once
#include <Eigen/Core>
class Shader
{
public:
	Shader();

	int LoadShaderString(const char* vertexShader, const char* fragmentShader);
	int LoadShaderFile(const char* vertexShaderPath, const char* fragmentShaderPath);

	Shader* Use();

	// ...set function
	int SetInt(const char* name, int val);
	int SetFloat(const char* name, float val);
	int SetVector3f(const char* name, Eigen::Vector3f vec);
	int SetVector4f(const char* name, Eigen::Vector4f vec);
	int SetMatrix4f(const char* name, Eigen::Matrix4f mat);

	unsigned int GetID() { return mShaderProgram; }
private:

	unsigned int mVertexShader;
	unsigned int mFragmentShader;

	unsigned int mShaderProgram;
};