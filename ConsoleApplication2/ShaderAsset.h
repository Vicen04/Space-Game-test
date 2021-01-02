#pragma once
#include <map>
#include <string>

typedef unsigned int GLuint;
typedef char GLchar;

class Shader
{
public:
	Shader();
	Shader(char* path);
	~Shader();
	void AddShader(char* vertexShaderpath, char* fragmentShaderpath, std::string shaderName);
	void SetShader(std::string shaderName);
	GLuint GetShaderToInit(std::string shaderName) { return ShaderProgram.at(shaderName);}


private:
	const GLchar* pVertexShaderCode;
	const GLchar* pFragmentShaderCode;
	std::map<std::string, GLuint> ShaderProgram;
};

