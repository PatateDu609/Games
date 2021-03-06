#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <glm/glm.hpp>

#include "Rectangle.h"
#include "GroupedShape.h"
#include "Score.h"

class Field;

class Snake : public GroupedShape
{
public:
	Snake(Field *f);

	void move();
	void setEaten(Score* eaten);

	virtual void draw();

private:
	unsigned int length;
	Field* field;
	Score* eaten;
	std::deque<glm::vec2> positions;
	Rectangle rect;

	bool areOpposite(int lastKey, int key) const;
	void update(int key);
	bool moving;

	void rules();
	void reset();
};

#endif // !SNAKE_H
