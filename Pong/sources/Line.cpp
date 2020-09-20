#include "../headers/Line.h"

Line::Line(glm::vec2 size) : Shape2D(GL_STATIC_DRAW)
{
	glm::vec3 color(255.0f);
	addVertex(glm::vec3(0.0f, 0.0f, 0.0f), color);
	addVertex(glm::vec3(0.0f, 1.0f, 0.0f), color);
	addVertex(glm::vec3(1.0f, 0.0f, 0.0f), color);
	addVertex(glm::vec3(1.0f, 0.0f, 0.0f), color);
	addVertex(glm::vec3(0.0f, 1.0f, 0.0f), color);
	addVertex(glm::vec3(1.0f, 1.0f, 0.0f), color);

	pos = glm::vec3(0.0f, 0.2f * size.y, 0.0f);

	glm::mat4 model(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, glm::vec3(size.x, 0.005f * size.y, 1.0f));
	this->model(model);
}

glm::vec3 Line::getPos() const
{
	return pos;
}