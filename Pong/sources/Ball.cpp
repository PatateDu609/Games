#include "../headers/Ball.h"

Ball::Ball(glm::vec2 size) : Shape2D(), accel(1.0f), radius(8.125f), baseSpeed(6),
	paddles({NULL, NULL}), topBound(NULL)
{
	pos = glm::vec3(size.x / 2.0f, size.y / 2.0f, 0.0f);
	speed = glm::vec2(1.0f, 0.1f);
	glm::vec3 center(0.0f);
	float radius = 8.125f;
	unsigned int sides = 16;

	glm::ivec3 color(255);

	for (unsigned int i = 0; i < sides; i++)
	{
		float angle = glm::radians(360.0f / static_cast<float>(sides));
		float x = cosf(i * angle);
		float x1 = cosf((i + 1) * angle);
		float y = sinf(i * angle);
		float y1 = sinf((i + 1) * angle);

		addVertex(glm::vec3(x, y, 0.0f), color);
		addVertex(center, color);
		addVertex(glm::vec3(x1, y1, 0.0f), color);
	}

	glm::mat4 model(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, glm::vec3(radius, radius, 1.0f));
	this->model(model);
}

void Ball::update(glm::vec2 size, glm::vec2 mouse)
{
	(void)mouse;

	pos.x += baseSpeed * speed.x * accel.x;
	pos.y += baseSpeed * speed.y * accel.y;

	if (pos.x + radius > size.x || pos.x - radius < 0)
	{
		bool who = pos.x - radius < 0;

		pos.x = size.x / 2.0f;
		pos.y = size.y / 2.0f;
		speed.y = 0.0f;
		accel.x = accel.y = speed.x = 1.0f;
		score->increase(who);
	}
	if (((topBound && pos.y - radius < topBound->getPos().y) || 
		(pos.y + radius > size.y)) || pos.y - radius < 0)
		speed.y *= -1;

	bool p1;
	if ((p1 = isColliding(paddles[0], true)) || isColliding(paddles[1], false))
	{
		pos.x = pos.x > (size.x / 2.0f) ? paddles[0]->getPos().x - radius :
			paddles[1]->getPos().x + paddles[0]->getSize().x + radius;
		collide(p1 ? paddles[0] : paddles[1]);
	}

	glm::mat4 model(1.0f);
	model = glm::translate(model, pos);
	model = glm::scale(model, glm::vec3(radius, radius, 1.0f));
	this->model(model);
}

void Ball::collide(const Paddle *paddle)
{
	float relativeIntersectY = (paddle->getPos().y + (paddle->getSize().y / 2.0f)) - pos.y;
	float normalizedRelativeIntersectY = relativeIntersectY / (paddle->getSize().y / 2.0f);
	float bounceAngle = normalizedRelativeIntersectY * glm::radians(75.0f);
	speed.x = cosf(bounceAngle);
	speed.y = -sinf(bounceAngle);
	if (paddle->getPos().x > pos.x)
		speed.x *= -1;
	accel.x *= 1.2f;
	accel.y *= 1.2f;
}

bool Ball::isColliding(const Paddle* pad, bool mode) const
{
	bool xCheck = false, yCheck = false;

	if ((mode && pos.x + radius > pad->getPos().x) ||
		(!mode && pos.x - radius < pad->getPos().x + pad->getSize().x))
		xCheck = true;
	if (pad->getPos().y < pos.y && pos.y < pad->getPos().y + pad->getSize().y)
		yCheck = true;
	if (!yCheck && (pos.y + radius < pos.y || pos.y - radius > pos.y))
		yCheck = true;
	return (xCheck && yCheck);
}

void Ball::setPaddles(const Paddle* p1, const Paddle* p2)
{
	paddles[0] = p1;
	paddles[1] = p2;
}

void Ball::setLine(const Line* line)
{
	this->topBound = line;
}

void Ball::setScore(Score* score)
{
	this->score = score;
}

glm::vec2 Ball::getPos() const
{
	return pos;
}

glm::vec2 Ball::getSpeed() const
{
	return speed;
}