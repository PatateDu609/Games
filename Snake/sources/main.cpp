#include <iostream>
#include <filesystem>

#include "../headers/Window.h"
#include "../headers/Texture.h"
#include "../headers/TexturedShape.h"
#include "../headers/Font.h"
#include "../headers/ressources_loader.h"

#include "../headers/Apple.h"
#include "../headers/Field.h"
#include "../headers/Snake.h"

#include "../headers/Rectangle.h"

int main()
{
	std::string name = "Snake";

	std::filesystem::path shadersPath = 
		std::filesystem::absolute(std::filesystem::path("../" + name + "/shaders"));
	std::filesystem::path texturesPath = 
		std::filesystem::absolute(std::filesystem::path("../" + name + "/textures"));
	std::filesystem::path fontsPath = 
		std::filesystem::absolute(std::filesystem::path("../" + name + "/fonts"));
	Ressources::setPrefix(Ressources::Type::SHADERS, shadersPath.string());
	Ressources::setPrefix(Ressources::Type::TEXTURES, texturesPath.string());
	Ressources::setPrefix(Ressources::Type::FONTS, fontsPath.string());


	glm::vec2 size = glm::vec2(600.0f, 600.0f);

	Window window(static_cast<unsigned int>(floor(size.x)), 
		static_cast<unsigned int>(floor(size.y)), name);
	window.init();

	Field field(size, 60, 60);
	Apple* apple = field.getApple();
	apple->setShader(Ressources::load("colored.vert"), Ressources::load("colored.frag"));
	window.addShape(apple);

	/*Rectangle rectangle(GL_DYNAMIC_DRAW, glm::ivec3(255));
	rectangle.setColor(glm::ivec3(0, 255, 0));
	rectangle.setShader(Ressources::load("colored.vert"), Ressources::load("colored.frag"));

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(size.x / 2.0f, size.y / 2.0f, 0.0f));
	model = glm::scale(model, glm::vec3(200, 200, 1));
	rectangle.model(model);

	rectangle.setColor(glm::ivec3(255, 0, 0));
	window.addShape(&rectangle);*/

	Snake snake(&field);
	window.addGroupedShape(&snake);

	window.setBg(glm::ivec3(0));
	window.display();
	delete apple;
	return (0);
}