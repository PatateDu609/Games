#include "../headers/Field.h"
#include "../headers/Apple.h"
#include <glm/gtc/random.hpp>

Field::Field(glm::vec2 wsize, int w, int h) : size(wsize), absSize(w, h),
	cellSize(size.x / static_cast<float>(w), size.y / static_cast<float>(h)), apple(NULL)
{
	apple = new Apple(this);
}

glm::ivec2 Field::getRandomPos() const
{
	std::srand(std::time(0));
	int x = glm::linearRand(0, absSize.x);
	int y = glm::linearRand(0, absSize.y);
	return glm::ivec2(x, y);
}

glm::vec3 Field::getCellScale() const
{
	return glm::vec3(cellSize.x, cellSize.y, 1.0f);
}

glm::vec3 Field::getTranslation(glm::ivec2 pos) const
{
	return glm::vec3(pos.x * cellSize.x, pos.y * cellSize.y, 0.0f);
}

Apple* Field::getApple()
{
	return apple;
}