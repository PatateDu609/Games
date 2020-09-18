#ifndef SHAPE2D_H
#define SHAPE2D_H

#include "Shader.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Shape2D
{
public:
	Shape2D();
	~Shape2D();

	void addVertex(glm::vec3 coord);
	void addVertex(glm::vec3 coord, glm::ivec3 color);

	void model(glm::mat4 &model);
	void projection(glm::mat4 &projection);

	void setShader(std::string vertexShader, std::string fragmentShader);

	virtual void update(glm::vec2 size, glm::vec2 mouse) = 0;
	void config();
	void draw();

private:
	unsigned int VAO;
	unsigned int VBO;
	Shader *shader;
	std::vector<float> data;
	bool configured;
	unsigned int vertexCount;

	glm::mat4 _model;
	glm::mat4 _projection;
};

#endif // !SHAPE2D_H
