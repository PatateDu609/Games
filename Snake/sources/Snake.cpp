#include "../headers/Snake.h"
#include "../headers/Field.h"
#include "../headers/ressources_loader.h"
#include "../headers/Window.h"
#include <algorithm>

Snake::Snake(Field *f) : field(f), rect(GL_DYNAMIC_DRAW, glm::ivec3(255, 255, 0)), length(5)
{
	positions.push_front(field->getCenter());

	rect.setShader(Ressources::load("colored.vert") , Ressources::load("colored.frag"));
	rect.config();
}

void Snake::move()
{
	int max = *std::max_element(arrows.begin(), arrows.end());
	static int lastKey = -1;

	if (max != -1)
	{
		int key = std::find(arrows.begin(), arrows.end(), max) - arrows.begin();
		if (!areOpposite(lastKey, key))
		{
			lastKey = key;
			update(key);
		}
	}
	else if (lastKey != -1)
		update(lastKey);
}

void Snake::draw()
{
	move();
	glm::mat4 model;

	for (glm::ivec2 pos : positions)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, field->getTranslation(pos));
		model = glm::scale(model, field->getCellScale());
		rect.model(model);
		rect.projection(_projection);
		rect.draw();
	}
}

bool Snake::areOpposite(int lastKey, int key) const
{
	if (lastKey == -1)
		return (false);
	if (key == RIGHT && lastKey == LEFT)
		return (true);
	if (key == LEFT && lastKey == RIGHT)
		return (true);
	if (key == UP && lastKey == DOWN)
		return (true);
	if (key == DOWN && lastKey == UP)
		return (true);
	return (false);
}

void Snake::update(int key)
{
	glm::ivec2 last = positions[0];

	switch (key)
	{
	case UP:
		positions.push_front(glm::ivec2(last.x, last.y + 1));
		break;
	case DOWN:
		positions.push_front(glm::ivec2(last.x, last.y - 1));
		break;
	case RIGHT:
		positions.push_front(glm::ivec2(last.x + 1, last.y));
		break;
	case LEFT:
		positions.push_front(glm::ivec2(last.x - 1, last.y));
		break;
	}
	if (positions.size() > length)
		positions.pop_back();
}
