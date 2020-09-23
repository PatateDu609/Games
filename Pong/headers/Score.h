#ifndef SCORE_H
#define SCORE_H

#include "Text.h"
#include "GroupedShape.h"

class Score : public GroupedShape
{
public:
	Score(Font& font, glm::vec2 size, unsigned char s1 = 0, unsigned char s2 = 0);

	void increase(bool player);
	void reset();
	virtual void draw();

private:
	Text p1;
	Text p2;
	unsigned char scores[2];

	void config(bool who, Font& font, std::string content);
};

#endif // !SCORE_H
