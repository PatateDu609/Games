#include "../headers/Font.h"
#include <iostream>
#include <vector>
#include <algorithm>

Font::Font(std::string font)
{
	FT_Library FT;
	FT_Face face;

	if (FT_Init_FreeType(&FT))
		std::cerr << "Error : FreeType : Failed to initialize the library" << std::endl;
	if (FT_New_Face(FT, font.c_str(), 0, &face))
		std::cerr << "Error : FreeType : Failed to load face" << std::endl;
	FT_Set_Pixel_Sizes(face, 0, 48);
	loadAscii(face, true);
	FT_Done_Face(face);
	FT_Done_FreeType(FT);
}

Font::~Font()
{
}

Font::Character::Character(FT_Face& face) :
	size(face->glyph->bitmap.width, face->glyph->bitmap.rows),
	bearing(face->glyph->bitmap_left, face->glyph->bitmap_top),
	advance(face->glyph->advance.x),
	texture(NULL)
{
	if (face->glyph->bitmap.buffer)
	{
		texture = new Texture(0, face->glyph->bitmap.buffer, size.x, size.y, 1);
		texture->load();
		texture->textureFilter(GL_NEAREST, GL_NEAREST);
		texture->textureWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
	}
}

Font::Character::Character()
{

}

void Font::loadAscii(FT_Face face, bool flush)
{
	if (flush)
		characters.clear();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (unsigned char c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cerr << "Error : FreeType : Failed to load glyph of " << std::hex << c;
			std::cerr << "(" << c << ")" << std::endl;
			continue;
		}
		characters.insert(std::pair<char, Character>(c, Character(face)));
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

Font::Character& Font::getChar(char c)
{
	return characters[c];
}

float Font::getWidth(std::string str, float scale)
{
	float result = 0.0f;
	float glyphWidth;

	for (int i = 0; i < str.size(); i++)
	{
		glyphWidth = (getChar(str[i]).advance >> 6) * scale;
		result += glyphWidth;
	}
	return result;
}

float Font::getHeight(std::string str, float scale)
{
	std::vector<float> bearingsY;
	std::vector<float> offsets;

	for (int i = 0; i < str.size(); i++)
	{
		Character ch = getChar(str[i]);
		float offset = (ch.size.y - ch.bearing.y) * scale;

		bearingsY.push_back(getChar(str[i]).bearing.y * scale);
		offsets.push_back(offset);
	}
	float result = *std::max_element(bearingsY.begin(), bearingsY.end()) +
		*std::max_element(offsets.begin(), offsets.end());
	return result;
}
