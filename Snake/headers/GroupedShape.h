#ifndef GROUPED_SHAPE_H
#define GROUPED_SHAPE_H

#include <glm/glm.hpp>

class GroupedShape
{
public:
	virtual void draw() = 0;
	void projection(glm::mat4& proj)
	{
		this->_projection = proj;
	}

	void setSize(glm::vec2 size)
	{
		this->size = size;
	}

protected:
	glm::mat4 _projection;
	glm::vec2 size;
};

#endif // !GROUPED_SHAPE_H
