#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include "Texture.h"

class Shader
{
public:
	Shader(const char* vertexShader, const char* fragmentShader);

	void use() const;

	void setBool(const char *name, bool val) const;
	void setInt(const char* name, int val) const;
	void setFloat(const char* name, float val) const;
	void setVec2(const char* name, float x, float y) const;
	void setVec2(const char* name, glm::vec2 &vec) const;
	void setVec3(const char* name, float x, float y, float z) const;
	void setVec3(const char* name, glm::vec3 &vec) const;
	void setVec4(const char* name, float x, float y, float z, float w) const;
	void setVec4(const char* name, glm::vec4 &vec) const;

	void setMat2(const char* name, glm::mat2 &mat) const;
	void setMat3(const char* name, glm::mat3 &mat) const;
	void setMat4(const char* name, glm::mat4 &mat) const;

	void useTexture(const char *name, const Texture& tex) const;

	unsigned int getID() const;

private:
	unsigned int _ID;
};

#endif