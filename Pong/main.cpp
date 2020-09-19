#include <iostream>
#include "Window.h"
#include "Ball.h"
#include "Paddle.h"
#include "Line.h"

int main()
{
	glm::vec2 size = glm::vec2(600.0f, 500.0f);
	Window window(size.x, size.y, "Pong");
	window.init();

	Ball ball(size);
	Paddle p1(size, true, false);
	Paddle p2(size, false, false);
	Line line(size);

	ball.setPaddles(&p1, &p2);
	ball.setLine(&line);
	p1.setBall(&ball);
	p2.setBall(&ball);

	ball.setShader("triangle.vert", "triangle.frag");
	p1.setShader("triangle.vert", "triangle.frag");
	p2.setShader("triangle.vert", "triangle.frag");
	line.setShader("triangle.vert", "triangle.frag");
	window.addShape(&ball);
	window.addShape(&p2);
	window.addShape(&p1);
	window.addShape(&line);
	window.setBg(glm::ivec3(0));
	window.display();

	return (0);
}