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
	int x, y;
	
	std::srand((unsigned int)std::time(NULL));
	do
	{
		x = glm::linearRand(0, absSize.x - 1);
		y = glm::linearRand(0, absSize.y - 1);
	} while (x == static_cast<int>(size.x / 2) || y == static_cast<int>(size.y / 2));
	return glm::ivec2(x, y);
}

glm::vec3 Field::getCellScale() const
{
	return glm::vec3(cellSize.x, cellSize.y, 1.0f);
}

glm::vec3 Field::getTranslation(glm::vec2 pos) const
{
	return glm::vec3(
		pos.x * cellSize.x + (cellSize.x / 2.0f), 
		pos.y * cellSize.y + (cellSize.y / 2.0f), 
		0.0f
	);
}

Apple* Field::getApple()
{
	return apple;
}

glm::ivec2 Field::getCenter() const
{
	return glm::ivec2(absSize.x / 2, absSize.y / 2);
}

bool Field::checkBounds(glm::vec2 pos) const
{
	return !((0 <= pos.x && pos.x < absSize.x) && (0 <= pos.y && pos.y < absSize.y));
}
