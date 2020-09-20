#ifndef MOVINGSHAPE_H
#define MOVINGSHAPE_H

#include "Shape2D.h"

class MovingShape
{
public:
	virtual void update(glm::vec2 size, glm::vec2 mouse) = 0;

protected:
	glm::vec3 pos;
	glm::vec2 speed;
};

#endif // !MOVINGSHAPE_H
