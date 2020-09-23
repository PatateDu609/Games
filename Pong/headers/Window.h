#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <array>
#include <vector>
#include "Shape2D.h"
#include "Text.h"
#include "MovingShape.h"
#include "GroupedShape.h"

#include <glm/glm.hpp>

class Window
{
public:
	typedef void (*MouseInputCallback)(GLFWwindow*, int, int, int);
	typedef void (*KeyboardInputCallback)(GLFWwindow*, int, int, int, int);
	typedef void (*FramebufferSizeCallback)(GLFWwindow*, int, int);

	Window(const Window& other) = delete;
	Window& operator=(const Window& other) = delete;

	Window();
	Window(unsigned int w, unsigned int h, std::string title);
	~Window();

	void setMouseInputCallback(MouseInputCallback fun) const;
	void setKeyboardInputCallback(KeyboardInputCallback fun) const;
	void setFramebufferSizeCallback(FramebufferSizeCallback fun) const;

	void setBg(glm::ivec3 color);
	void setBg(glm::ivec4 color);
	void setTitle(std::string title);
	void setSize(glm::ivec2 vec);
	void setSize(std::array<int, 2> size);
	void setSize(int size[2]);
	void setSize(int w, int h);

	void addShape(Shape2D *shape);
	void addText(Text *text);
	void addGroupedShape(GroupedShape *text);

	bool init();
	void display();

private:
	GLFWwindow* _window;
	int _w;
	int _h;
	std::string _title;
	glm::vec4 _bg;

	std::vector<Shape2D *> _shapes;
	std::vector<Text*> _textes;
	std::vector<GroupedShape*> _groupedShapes;

	static unsigned int _count;
};

void processInput(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebufferSize(GLFWwindow* window, int w, int h);


enum KEYS
{
	UP = 0,
	DOWN = 1,
	W = 2,
	S = 3
};
extern std::array<int, 4> arrows;

#endif // !WINDOW_H
