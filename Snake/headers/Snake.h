#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <glm/glm.hpp>

#include "Rectangle.h"
#include "GroupedShape.h"

class Field;

class Snake : public GroupedShape
{
public:
	Snake(Field *f);

	void move();

	virtual void draw();

private:
	unsigned int length;
	Field* field;
	std::deque<glm::ivec2> positions;
	Rectangle rect;

	bool areOpposite(int lastKey, int key) const;
	void update(int key);
};

#endif // !SNAKE_H
