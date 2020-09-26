#include "../headers/Score.h"
#include "../headers/ressources_loader.h"

Score::Score(Font& font, glm::vec2 size) : text(font), score(0)
{
	setSize(size);
	text.setContent("Score : " + std::to_string(score));
	text.setColor(glm::ivec3(255));
	text.setShader(Ressources::load("text.vert"), Ressources::load("text.frag"));
}

void Score::increase()
{
	score++;
	text.setContent("Score : " + std::to_string(score));
}

void Score::reset()
{
	score = 0;
	text.setContent("Score : " + std::to_string(score));
}

void Score::setCoord(glm::vec2 coord)
{
	text.setCoord(coord);
}

void Score::draw()
{
	text.getShader()->use();
	text.getShader()->setFloat("sizeY", size.y);
	text.projection(_projection);
	text.draw();
}
