#ifndef BALL_H
#define BALL_H

#include "Shape2D.h"
#include "Paddle.h"
#include "MovingShape.h"
#include "Window.h"
#include <array>

class Paddle;

class Ball : public Shape2D, public MovingShape
{
public:
	Ball(glm::vec2 size);

	virtual void update(glm::vec2 size, glm::vec2 mouse);

	void setPaddles(const Paddle* p1, const Paddle* p2);

	glm::vec2 getPos() const;
	glm::vec2 getSpeed() const;

private:
	/*glm::vec3 pos;
	glm::vec2 speed;*/
	glm::vec2 accel;

	const float radius;
	const float baseSpeed;

	std::array<const Paddle*, 2> paddles;

	void collide(const Paddle *paddle);
	bool isColliding(const Paddle *pad, bool mode) const;
};

#endif // !BALL_H
