#pragma once
#include "structures.h"
#include <map>

class Shader
{
public:
	Shader();
	Shader(char* path);
	~Shader();
	void AddShader(char* vertexShaderpath, char* fragmentShaderpath, string shaderName);
	void SetShader(string shaderName);
	GLuint GetShaderToInit(string shaderName) { return ShaderProgram.at(shaderName);}


private:
	const GLchar* pVertexShaderCode;
	const GLchar* pFragmentShaderCode;
	std::map<string, GLuint> ShaderProgram;
};

