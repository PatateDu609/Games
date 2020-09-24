#include "../headers/Apple.h"
#include "../headers/Field.h"

Apple::Apple(Field *f) : Shape2D(GL_STATIC_DRAW), field(f)
{
	setPos(field->getRandomPos());

	addVertex(glm::vec3(-0.5f, -0.5f, 0.0f));
	addVertex(glm::vec3(0.5f, -0.5f, 0.0f));
	addVertex(glm::vec3(-0.5f, 0.5f, 0.0f));

	addVertex(glm::vec3(-0.5f, 0.5f, 0.0f));
	addVertex(glm::vec3(0.5f, 0.5f, 0.0f));
	addVertex(glm::vec3(0.5f, -0.5f, 0.0f));
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
