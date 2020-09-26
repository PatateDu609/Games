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
#include "../headers/Score.h"

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


	glm::vec2 size = glm::vec2(1200.0f, 600.0f);

	Window window(static_cast<unsigned int>(floor(size.x)), 
		static_cast<unsigned int>(floor(size.y)), name);
	window.init();

	Field field(glm::vec2(size.x / 2.0f, size.y), glm::vec2(size.x / 2.0f, 0.0f) , 60, 60);
	Apple* apple = field.getApple();
	apple->setShader(Ressources::load("colored.vert"), Ressources::load("colored.frag"));
	window.addShape(apple);

	Snake snake(&field);
	window.addGroupedShape(&snake);

	Rectangle line(GL_STATIC_DRAW, glm::ivec3(255));
	line.setShader(Ressources::load("colored.vert"), Ressources::load("colored.frag"));
	window.addShape(&line);
	
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(595.0f, size.y / 2.0f, 0.0f));
	model = glm::scale(model, glm::vec3(5.0f, size.y, 1.0f));
	line.model(model);

	Font font(Ressources::load("04b-03.ttf"));
	Score score(font, glm::vec2(size.x / 2.0f, size.y));
	score.setCoord(glm::vec2(((size.x / 2.0f) - font.getWidth("Score : 0", 1.0f)) / 2.0f,
		(size.y + font.getHeight("Score : 0", 1.0f)) / 2.0f));
	window.addGroupedShape(&score);

	snake.setEaten(&score);

	window.setBg(glm::ivec3(0));
	window.display();
	delete apple;
	return (0);
}