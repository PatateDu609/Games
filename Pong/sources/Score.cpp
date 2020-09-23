#include "../headers/Score.h"
#include "../headers/ressources_loader.h"

void Score::config(bool who, Font& font, std::string content)
{
	float scale = 2.25f;
	float w = font.getChar(content[0]).size.x * scale;
	float h = font.getHeight(content, scale);
	float xOffset = 50;
	float xCoord;
	float yCoord = h + size.x * 0.025f;
	Text* player;

	if (!who)
	{
		xCoord = xOffset;
		player = &p2;
	}
	else
	{
		xCoord = size.x - w - xOffset;
		player = &p1;
	}

	player->setSize(size);
	player->setColor(glm::ivec3(255, 255, 255));
	player->setCoord(xCoord, yCoord);
	player->setScale(scale);
	player->setShader(Ressources::load("text.vert"), Ressources::load("text.frag"));
}

Score::Score(Font& font, glm::vec2 size, unsigned char s1, unsigned char s2) : 
	scores{ 0, 0 }, p1(font), p2(font)
{
	s1 = std::max(s1, static_cast<unsigned char>(10));
	s2 = std::max(s2, static_cast<unsigned char>(10));
	if (s1 == 10 || s2 == 10)
		s1 = s2 = 0;
	scores[0] = s1;
	scores[1] = s2;

	setSize(size);

	std::string c1 = std::to_string(s1);
	std::string c2 = std::to_string(s2);

	p1.setContent(c1);
	config(true, font, c1);
	p2.setContent(c2);
	config(false, font, c2);
}

void Score::increase(bool player)
{
	std::cout << static_cast<size_t>(!player) << std::endl;

	scores[static_cast<size_t>(!player)]++;
	if (scores[0] == 10 || scores[1] == 10)
		reset();
}

void Score::reset()
{
	scores[0] = scores[1] = 0;
}

void Score::draw()
{
	p1.setContent(std::to_string(scores[0]));
	p1.projection(_projection);
	p1.setSize(size);
	p1.draw();

	p2.setContent(std::to_string(scores[1]));
	p2.projection(_projection);
	p2.setSize(size);
	p2.draw();
}