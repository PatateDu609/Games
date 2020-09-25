#include "../headers/Window.h"

std::array<int, 4> arrows = { -1, -1, -1, -1 };

void processInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static int i = 0;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (key == GLFW_KEY_UP && action != GLFW_REPEAT)
		arrows[UP] = action != GLFW_RELEASE ? i++ : -1;
	else if (key == GLFW_KEY_DOWN && action != GLFW_REPEAT)
		arrows[DOWN] = action != GLFW_RELEASE ? i++ : -1;
	else if (key == GLFW_KEY_RIGHT && action != GLFW_REPEAT)
		arrows[RIGHT] = action != GLFW_RELEASE ? i++ : -1;
	else if (key == GLFW_KEY_LEFT && action != GLFW_REPEAT)
		arrows[LEFT] = action != GLFW_RELEASE ? i++ : -1;
}

void framebufferSize(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}