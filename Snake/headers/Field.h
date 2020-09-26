#ifndef FIELD_H
#define FIELD_H

#include <glm/glm.hpp>

class Apple;

class Field
{
public:
	Field(glm::vec2 wsize, glm::vec2 woffset, int w, int h);
	
	glm::ivec2 getRandomPos() const;

	glm::vec3 getCellScale() const;
	glm::vec3 getTranslation(glm::vec2 pos) const;
	glm::ivec2 getCenter() const;
	bool checkBounds(glm::vec2 pos) const;

	Apple* getApple();

private:
	Apple* apple;
	glm::vec2 size;
	glm::vec2 cellSize;
	glm::ivec2 absSize;
	glm::vec2 offset;
};

#endif // !FIELD_H
