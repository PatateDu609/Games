#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape2D.h"

class Rectangle : public Shape2D
{
public:
	Rectangle(GLint usage = GL_DYNAMIC_DRAW, glm::ivec3 color = glm::ivec3(163, 112, 232));

	void setColor(glm::ivec3 color);

private:

};

#endif // !RECTANGLE_H
