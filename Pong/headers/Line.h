#ifndef LINE_H
#define LINE_H

#include "Shape2D.h"

class Line : public Shape2D
{
public:
	Line(glm::vec2 size);

	glm::vec3 getPos() const;

private:
	glm::vec3 pos;
};

#endif // !LINE_H
