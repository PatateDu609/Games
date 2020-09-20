#include "Shader.h"
#include <sstream>

Shader::Shader(const char* vertexShader, const char* fragmentShader)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vsFile;
	std::ifstream fsFile;

	vsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vsFile.open(vertexShader);
		fsFile.open(fragmentShader);

		std::ostringstream vsBuf, fsBuf;
		vsBuf << vsFile.rdbuf();
		fsBuf << fsFile.rdbuf();
		vsFile.close();
		fsFile.close();

		vertexCode = vsBuf.str();
		fragmentCode = fsBuf.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "ERROR : couldn't read file" << std::endl;
	}

	int success;
	char infoLog[512];
	unsigned int vs, fs;
	vs = glCreateShader(GL_VERTEX_SHADER);
	fs = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vsText = vertexCode.c_str();
	const char* fsText = fragmentCode.c_str();
	glShaderSource(vs, 1, &vsText, NULL);
	glShaderSource(fs, 1, &fsText, NULL);

	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vs, 512, NULL, infoLog);
		std::cerr << "Vertex Shader : " << infoLog << std::endl;
	}

	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fs, 512, NULL, infoLog);
		std::cerr << "Fragment Shader : " << infoLog << std::endl;
	}

	_ID = glCreateProgram();
	glAttachShader(_ID, vs);
	glAttachShader(_ID, fs);
	glLinkProgram(_ID);

	glGetProgramiv(_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_ID, 512, NULL, infoLog);
		std::cerr << "Program Link: " << infoLog << std::endl;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
}

void Shader::use() const
{
	glUseProgram(_ID);
}

void Shader::setBool(const char* name, bool val) const
{
	unsigned int loc = glGetUniformLocation(_ID, name);
	glUniform1i(loc, val);
}

void Shader::setFloat(const char* name, float val) const
{
	unsigned int loc = glGetUniformLocation(_ID, name);
	glUniform1f(loc, val);
}

void Shader::setInt(const char* name, int val) const
{
	unsigned int loc = glGetUniformLocation(_ID, name);
	glUniform1i(loc, val);
}

unsigned int Shader::getID() const
{
	return _ID;
}

void Shader::setVec2(const char* name, float x, float y) const
{
	unsigned int loc = glGetUniformLocation(_ID, name);
	glUniform2f(loc, x, y);
}

void Shader::setVec3(const char* name, float x, float y, float z) const
{
	unsigned int loc = glGetUniformLocation(_ID, name);
	glUniform3f(loc, x, y, z);
}

void Shader::setVec4(const char* name, float x, float y, float z, float w) const
{
	unsigned int loc = glGetUniformLocation(_ID, name);
	glUniform4f(loc, x, y, z, w);
}

void Shader::setVec2(const char* name, glm::vec2& vec) const
{
	unsigned int loc = glGetUniformLocation(_ID, name);
	glUniform2fv(loc, 1, &vec[0]);
}

void Shader::setVec3(const char* name, glm::vec3& vec) const
{
	unsigned int loc = glGetUniformLocation(_ID, name);
	glUniform3fv(loc, 1, &vec[0]);
}

void Shader::setVec4(const char* name, glm::vec4& vec) const
{
	unsigned int loc = glGetUniformLocation(_ID, name);
	glUniform4fv(loc, 1, &vec[0]);
}

void Shader::setMat2(const char* name, glm::mat2& mat) const
{
	unsigned int loc = glGetUniformLocation(_ID, name);
	glUniformMatrix2fv(loc, 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const char* name, glm::mat3& mat) const
{
	unsigned int loc = glGetUniformLocation(_ID, name);
	glUniformMatrix3fv(loc, 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const char* name, glm::mat4& mat) const
{
	unsigned int loc = glGetUniformLocation(_ID, name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
}

void Shader::useTexture(const char *name, const Texture& tex) const
{
	setInt(name, tex.getSlot());
}