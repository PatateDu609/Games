#include "../headers/Apple.h"
#include "../headers/Field.h"

Apple::Apple(Field *f) : Shape2D(GL_STATIC_DRAW), field(f)
{
	setPos(field->getRandomPos());

	glm::ivec3 color(255, 0, 0);

	addVertex(glm::vec3(-0.5f, -0.5f, 0.0f), color);
	addVertex(glm::vec3(0.5f, -0.5f, 0.0f), color);
	addVertex(glm::vec3(-0.5f, 0.5f, 0.0f), color);

	addVertex(glm::vec3(-0.5f, 0.5f, 0.0f), color);
	addVertex(glm::vec3(0.5f, 0.5f, 0.0f), color);
	addVertex(glm::vec3(0.5f, -0.5f, 0.0f), color);
}

void Apple::setPos(glm::ivec2 pos)
{
	this->pos = pos;

	glm::mat4 model(1.0f);
	model = glm::translate(model, field->getTranslation(pos));
	model = glm::scale(model, field->getCellScale());
	this->model(model);
}


glm::ivec2 Apple::getPos() const
{
	return pos;
}
