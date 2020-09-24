#ifndef FONT_H
#define FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <map>
#include <string>
#include "Texture.h"

class Font
{
public:
	struct Character
	{
		Texture *texture;
		glm::ivec2 size;
		glm::ivec2 bearing;
		unsigned int advance;

		Character(FT_Face& face);
		Character();
	};

	Font(std::string font);
	~Font();

	float getWidth(std::string str, float scale);
	float getHeight(std::string str, float scale);

	Character& getChar(char c);

private:
	std::map<char, Character> characters;

	void loadAscii(FT_Face face, bool flush = false);
};

#endif // !FONT_H
