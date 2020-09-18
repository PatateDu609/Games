#ifndef PADDLE_H
#define PADDLE_H

#include "Shape2D.h"
#include "Window.h"
#include "Ball.h"

class Ball;

class Paddle : public Shape2D
{
public:
	Paddle(glm::vec2 wsize, bool mode, bool human);

	virtual void update(glm::vec2 size, glm::vec2 mouse);
	glm::vec3 getPos() const;
	glm::vec2 getSize() const;

	void setBall(const Ball *b);

private:
	bool player;
	glm::vec3 pos;
	glm::vec2 speed;
	glm::vec2 size;

	const Ball* ball;
	bool ia;
};

#endif // !PADDLE_H
