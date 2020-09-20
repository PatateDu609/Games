#include "../headers/Paddle.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

Paddle::Paddle(glm::vec2 wsize, bool mode, bool human) : player(mode), size(8.125f, 100.0f), ia(!human)
{
	pos = glm::vec3(0.0f);
	speed = glm::vec2(0.0f);

	glm::vec3 color(255.0f);
	ball = NULL;
	addVertex(glm::vec3(0.0f, 0.0f, 0.0f), color);
	addVertex(glm::vec3(0.0f, 1.0f, 0.0f), color);
	addVertex(glm::vec3(1.0f, 0.0f, 0.0f), color);
	addVertex(glm::vec3(1.0f, 0.0f, 0.0f), color);
	addVertex(glm::vec3(0.0f, 1.0f, 0.0f), color);
	addVertex(glm::vec3(1.0f, 1.0f, 0.0f), color);

	float ph = 0.96f;
	pos.x = (mode ? ph : 1 - ph) * wsize.x - mode * size.x;
	pos.y = (wsize.y - size.y) / 2.0f;
	glm::mat4 model(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, glm::vec3(size.x, size.y, 0.0f));
	this->model(model);
}

void Paddle::update(glm::vec2 wsize, glm::vec2 mouse)
{
	int mode = 0;
	
	if (!ia)
	{
		if (player)
		{
			mode = (arrows[UP] == -1 && arrows[DOWN] == -1) ? 0 : 1;
			mode *= (std::max(arrows[UP], arrows[DOWN]) == arrows[DOWN]) ? 1 : -1;
		}
		else
		{
			mode = (arrows[W] == -1 && arrows[S] == -1) ? 0 : 1;
			mode *= (std::max(arrows[W], arrows[S]) == arrows[S]) ? 1 : -1;
		}
	}
	else if ((player && ball->getSpeed().x > 0) || (!player && ball->getSpeed().x < 0))
	{
		if (pos.y + 0.1f * size.y < ball->getPos().y && ball->getPos().y < pos.y + 0.90f * size.y)
			mode = 0;
		else
			mode = (pos.y + (size.y / 2.0f) < ball->getPos().y) ? 1 : -1;
	}

	float delta = 6.0f * mode;
	pos.y += delta;
	
	if (pos.y < 0)
		pos.y = 0;
	else if (pos.y > wsize.y - size.y)
		pos.y = wsize.y - size.y;

	glm::mat4 model(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, glm::vec3(size.x, size.y, 0.0f));
	this->model(model);
}

glm::vec3 Paddle::getPos() const
{
	return pos;
}

glm::vec2 Paddle::getSize() const
{
	return size;
}

void Paddle::setBall(const Ball* ball)
{
	this->ball = ball;
}
