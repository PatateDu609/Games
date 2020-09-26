#include "../headers/Window.h"
#include <iostream>
#include "../headers/TexturedShape.h"

unsigned int Window::_count = 0;

Window::Window() : _window(NULL), _w(800), _h(600), _title("Window"), _bg(0.0f, 0.0f, 0.0f, 1.0f)
{
	if (!_count)
	{
		glfwInit();
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_REFRESH_RATE, 15);
	_count++;
}

Window::Window(unsigned int w, unsigned int h, std::string title) : Window()
{
	_w = w;
	_h = h;
	_title = title;
}

Window::~Window()
{
	_count--;
	glfwDestroyWindow(_window);
	if (!_count)
		glfwTerminate();
}

void Window::setMouseInputCallback(MouseInputCallback fun) const
{
	glfwSetMouseButtonCallback(_window, fun);
}

void Window::setKeyboardInputCallback(KeyboardInputCallback fun) const
{
	glfwSetKeyCallback(_window, fun);
}

void Window::setFramebufferSizeCallback(FramebufferSizeCallback fun) const
{
	glfwSetFramebufferSizeCallback(_window, fun);
}

void Window::setTitle(std::string title)
{
	_title = title;
	glfwSetWindowTitle(_window, title.c_str());
}

void Window::setSize(glm::ivec2 vec)
{
	_w = vec.x;
	_h = vec.y;
	glfwSetWindowSize(_window, vec.x, vec.y);
}

void Window::setSize(std::array<int, 2> size)
{
	_w = size[0];
	_h = size[1];
	glfwSetWindowSize(_window, size[0], size[1]);
}

void Window::setSize(int size[2])
{
	_w = size[0];
	_h = size[1];
	glfwSetWindowSize(_window, size[0], size[1]);
}

void Window::setSize(int w, int h)
{
	_w = w;
	_h = h;
	glfwSetWindowSize(_window, w, h);
}

void Window::setBg(glm::ivec3 color)
{
	_bg.x = (float)color.x / 255.0f;
	_bg.y = (float)color.y / 255.0f;
	_bg.z = (float)color.z / 255.0f;
	_bg.w = 1.0f;
}

void Window::setBg(glm::ivec4 color)
{
	_bg.x = (float)color.x / 255.0f;
	_bg.y = (float)color.y / 255.0f;
	_bg.z = (float)color.z / 255.0f;
	_bg.w = (float)color.w / 255.0f;
}

bool Window::init()
{
	_window = glfwCreateWindow(_w, _h, _title.c_str(), NULL, NULL);
	if (!_window)
		return (false);
	glfwMakeContextCurrent(_window);
	glfwSwapInterval(2);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return false;
	glfwSetFramebufferSizeCallback(_window, framebufferSize);
	glfwSetKeyCallback(_window, processInput);
	glViewport(0, 0, _w, _h);
	glEnable(GL_MULTISAMPLE);

	return (true);
}

void Window::display()
{
	glm::mat4 projection;
	double x, y;
	MovingShape* ms;
	TexturedShape* ts;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!glfwWindowShouldClose(_window))
	{
		glClearColor(_bg.x, _bg.y, _bg.z, _bg.w);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwGetFramebufferSize(_window, &_w, &_h);
		glfwGetCursorPos(_window, &x, &y);

		projection = glm::ortho(0.0f, static_cast<float>(_w), static_cast<float>(_h), 0.0f);
		for (Shape2D *shape : _shapes)
		{
			shape->projection(projection);
			if ((ms = dynamic_cast<MovingShape*>(shape)))
				ms->update(glm::vec2(_w, _h), glm::vec2(x, y));
			if ((ts = dynamic_cast<TexturedShape*>(shape)))
				ts->useTextures();
			shape->draw();
		}

		for (Text* text : _textes)
		{
			text->setSize(glm::vec2(_w, _h));
			text->projection(projection);
			text->draw();
		}

		for (GroupedShape* gs : _groupedShapes)
		{
			gs->projection(projection);
			//gs->setSize(glm::vec2(_w, _h));
			gs->draw();
		}

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
}

void Window::addShape(Shape2D* shape)
{
	shape->config();
	_shapes.push_back(shape);
}

void Window::addText(Text* text)
{
	_textes.push_back(text);
}

void Window::addGroupedShape(GroupedShape* gs)
{
	_groupedShapes.push_back(gs);
}
