#include "../headers/Rectangle.h"

Rectangle::Rectangle(GLint usage, glm::ivec3 color) : Shape2D(usage)
{
	addVertex(glm::vec3(-0.5f, -0.5f, 0.0f), color);
	addVertex(glm::vec3(0.5f, -0.5f, 0.0f), color);
	addVertex(glm::vec3(-0.5f, 0.5f, 0.0f), color);

	addVertex(glm::vec3(0.5f, -0.5f, 0.0f), color);
	addVertex(glm::vec3(0.5f, 0.5f, 0.0f), color);
	addVertex(glm::vec3(-0.5f, 0.5f, 0.0f), color);
}

void Rectangle::setColor(glm::ivec3 color)
{
	for (unsigned long i = 3; i < data.size(); i += 3)
	{
		data[i++] = static_cast<float>(color.x) / 255.0f;
		data[i++] = static_cast<float>(color.y) / 255.0f;
		data[i++] = static_cast<float>(color.z) / 255.0f;
	}
}
