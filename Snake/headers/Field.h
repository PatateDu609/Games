#ifndef FIELD_H
#define FIELD_H

#include <glm/glm.hpp>

class Apple;

class Field
{
public:
	Field(glm::vec2 wsize, int w, int h);
	
	glm::ivec2 getRandomPos() const;

	glm::vec3 getCellScale() const;
	glm::vec3 getTranslation(glm::ivec2 pos) const;
	glm::ivec2 getCenter() const;

	Apple* getApple();

private:
	Apple* apple;
	glm::vec2 size;
	glm::vec2 cellSize;
	glm::ivec2 absSize;
};

#endif // !FIELD_H
