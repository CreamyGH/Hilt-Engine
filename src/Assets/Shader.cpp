#include "Shader.h"

Shader::Shader()
{
	m_Program = glCreateProgram();
}

void Shader::AddShader(const char* path, GLenum shaderType)
{
	GLuint shader;
	shader = glCreateShader(shaderType);
	LoadShaderFromFile(path, shader);

	glAttachShader(m_Program, shader);
	glLinkProgram(m_Program);

	CheckProgramCompilation();

	glDeleteShader(shader);
}

int Shader::GetVarLocation(const char* name)
{
	return glGetUniformLocation(m_Program, name);
}

void Shader::UseProgram()
{
	glUseProgram(m_Program);
}

void Shader::LoadShaderFromFile(const char* path, GLuint& shader)
{
	std::ifstream file;
	std::stringstream buf;

	std::string out = "";

	file.open(path);
	if (!file.is_open())
	{
		std::cout << "Could not open file: " << path << std::endl;
		return;
	}

	buf << file.rdbuf();
	out = buf.str();
	file.close();

	const GLchar* shaderSource = out.c_str();

	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Error shader compilation failed in file: " << path << std::endl;
		std::cout << "Error message: " << std::endl << infoLog << std::endl;
		return;
	}
}

void Shader::CheckProgramCompilation()
{
	int success;
	char infoLog[512];

	glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_Program, 512, NULL, infoLog);
		std::cout << "Error shader program compilation failed" << std::endl;
		std::cout << "Error message: " << std::endl << infoLog << std::endl;
	}
}

//*------ SETS --------*//
void Shader::SetInt(const char* varName, int value)
{
	int location = GetVarLocation(varName);
	glUniform1i(location, value);
}

void Shader::SetFloat(const char* varName, float value)
{
	int location = GetVarLocation(varName);
	glUniform1f(location, value);
}

void Shader::SetVec2(const char* varName, glm::vec2 vector2)
{
	int location = GetVarLocation(varName);
	glUniform3fv(location, 1, glm::value_ptr(vector2));
}

void Shader::SetVec3(const char* varName, glm::vec3 vector3)
{
	int location = GetVarLocation(varName);
	glUniform3fv(location, 1, glm::value_ptr(vector3));
}

void Shader::SetMat4(const char* varName, glm::mat4 matrix)
{
	int location = GetVarLocation(varName);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

Shader::~Shader()
{
	glDeleteProgram(m_Program);
}