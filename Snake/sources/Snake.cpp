#include "../headers/Snake.h"
#include "../headers/Field.h"
#include "../headers/Apple.h"
#include "../headers/ressources_loader.h"
#include "../headers/Window.h"
#include <algorithm>

Snake::Snake(Field *f) : field(f), rect(GL_DYNAMIC_DRAW, glm::ivec3(255, 255, 0)), length(5),
	moving(true)
{
	positions.push_front(field->getCenter());

	rect.setShader(Ressources::load("colored.vert") , Ressources::load("colored.frag"));
	rect.config();
}

void Snake::move()
{
	static int lastKey = -1;

	if (!moving)
		lastKey = -1;

	if (!pause)
	{
		int max = *std::max_element(arrows.begin(), arrows.end());

		if (max != -1)
		{
			moving = true;
			int key = std::find(arrows.begin(), arrows.end(), max) - arrows.begin();
			if (!areOpposite(lastKey, key))
				lastKey = key;
		}
		if (lastKey != -1)
			update(lastKey);
		rules();
	}
}

void Snake::draw()
{
	move();
	glm::mat4 model;

	for (glm::vec2 pos : positions)
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
	glm::vec2 last = positions[0];
	float speed = 1.0f;
	int dir = (key == DOWN || key == RIGHT) ? 1 : -1;

	switch (key)
	{
	case UP: case DOWN:
		positions.push_front(glm::vec2(last.x, last.y + dir * speed));
		break;
	case RIGHT: case LEFT:
		positions.push_front(glm::vec2(last.x + dir * speed, last.y));
		break;
	}
	if (positions.size() > length)
		positions.pop_back();
}

void Snake::rules()
{
	glm::vec2 head = positions[0];

	if (field->checkBounds(head))
	{
		reset();
		return;
	}

	std::deque<glm::vec2>::iterator res = std::find(positions.begin() + 1, positions.end(), head);
	if (res != positions.end())
	{
		reset();
		return;
	}

	glm::vec2 applePos(field->getApple()->getPos());
	if (applePos.x == head.x && applePos.y == head.y)
	{
		field->getApple()->setPos(field->getRandomPos());
		length++;
		return;
	}
}

void Snake::reset()
{
	moving = false;
	length = 5;
	positions.clear();
	positions.push_front(field->getCenter());
}
