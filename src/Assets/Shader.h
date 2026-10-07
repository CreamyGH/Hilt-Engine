#pragma once

#include <iostream>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

class Shader
{
public:
	Shader();
	~Shader();

	void UseProgram();
	void AddShader(const char* path, GLenum shaderType);
	GLuint GetProgram() { return m_Program; }

	int GetVarLocation(const char* name);

	void SetInt(const char* varName, int value);
	void SetFloat(const char* varName, float value);
	void SetVec2(const char* varName, glm::vec2 vector2);
	void SetVec3(const char* varName, glm::vec3 vector3);
	void SetMat4(const char* varName, glm::mat4 matrix);

private:
	void LoadShaderFromFile(const char* path, GLuint& shader);
	void CheckProgramCompilation();

private:
	GLuint m_Program;
};