#ifndef APPLE_H
#define APPLE_H

#include "Shape2D.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Field;

class Apple : public Shape2D
{
public:
	Apple(Field *f);

	void setPos(glm::ivec2 pos);
	glm::ivec2 getPos() const;

private:
	glm::ivec2 pos;
	Field *field;
};

#endif // !APPLE_H
