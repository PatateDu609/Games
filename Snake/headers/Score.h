#ifndef SCORE_H
#define SCORE_H

#include "GroupedShape.h"
#include "Text.h"

class Score : public GroupedShape
{
public:
	Score(Font& font, glm::vec2 size);

	void increase();
	void reset();
	void setCoord(glm::vec2 coord);

	virtual void draw();

private:
	unsigned int score;
	Text text;
};

#endif // !SCORE_H
