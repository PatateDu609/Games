#include <iostream>
#include <filesystem>

#include "../headers/Window.h"
#include "../headers/Ball.h"
#include "../headers/Paddle.h"
#include "../headers/Line.h"
#include "../headers/Score.h"

#include "../headers/Texture.h"
#include "../headers/TexturedShape.h"

#include "../headers/Font.h"

#include "../headers/ressources_loader.h"

int main()
{
	std::filesystem::path shadersPath = std::filesystem::absolute(std::filesystem::path("../Pong/shaders"));
	std::filesystem::path texturesPath = std::filesystem::absolute(std::filesystem::path("../Pong/textures"));
	std::filesystem::path fontsPath = std::filesystem::absolute(std::filesystem::path("../Pong/fonts"));
	Ressources::setPrefix(Ressources::Type::SHADERS, shadersPath.string());
	Ressources::setPrefix(Ressources::Type::TEXTURES, texturesPath.string());
	Ressources::setPrefix(Ressources::Type::FONTS, fontsPath.string());


	glm::vec2 size = glm::vec2(600.0f, 500.0f);
	Window window(static_cast<unsigned int>(floor(size.x)), 
		static_cast<unsigned int>(floor(size.y)), "Pong");
	window.init();

	Ball ball(size);
	Paddle p1(size, true, false);
	Paddle p2(size, false, false);
	Line line(size);

	Font font(Ressources::load("04b-03.ttf"));
	Score score(font, size);


	ball.setPaddles(&p1, &p2);
	ball.setLine(&line);
	ball.setScore(&score);

	p1.setBall(&ball);
	p2.setBall(&ball);
	ball.setShader(Ressources::load("colored.vert"), Ressources::load("colored.frag"));
	p1.setShader(Ressources::load("colored.vert"), Ressources::load("colored.frag"));
	p2.setShader(Ressources::load("colored.vert"), Ressources::load("colored.frag"));
	line.setShader(Ressources::load("colored.vert"), Ressources::load("colored.frag"));
	window.addShape(&ball);
	window.addShape(&p2);
	window.addShape(&p1);
	window.addShape(&line);
	window.addGroupedShape(&score);

	Texture tex(0, Ressources::load("pause.png"), false);
	tex.textureFilter(GL_LINEAR, GL_LINEAR);
	tex.textureWrap(GL_REPEAT, GL_REPEAT);
	tex.load();

	TexturedShape texShape(&tex);
	texShape.addVertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f));
	texShape.addVertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f));
	texShape.addVertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f));

	texShape.addVertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f));
	texShape.addVertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f));
	texShape.addVertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f));

	glm::mat4 model(1.0f);

	float height = size.y * 0.12f;

	model = glm::translate(model, glm::vec3(size.x / 2.0f, size.y * 0.03f + height / 2.f, 1.0f));
	model = glm::scale(model, glm::vec3(height * 780.0f / 1072.0f, height, 1.0f));
	texShape.model(model);

	texShape.setShader(Ressources::load("textured.vert"), Ressources::load("textured.frag"));
	window.addShape(&texShape);
	window.setBg(glm::ivec3(0));
	window.display();

	return (0);
}