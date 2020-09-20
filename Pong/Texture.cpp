#include "Texture.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(unsigned int tex_slot, std::string filename, bool flip) :
	slot(tex_slot), ID(0), file(filename), width(0), height(0), channels(0)
{
	stbi_set_flip_vertically_on_load(flip);

	glGenTextures(1, &ID);
}

Texture::Texture(unsigned int tex_slot, unsigned char* image, int w, int h, int nbrChannel) :
	slot(tex_slot), ID(0), width(w), height(h), channels(nbrChannel)
{

}

bool Texture::load()
{
	if (!file.size())
		return (false);
	unsigned char* data = stbi_load(file.c_str(), &width, &height, &channels, STBI_rgb_alpha);
	if (!data)
		std::cerr << "Error : Texture : Failed to load the texture" << std::endl;
	use();
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	return (true);
}

void Texture::selectActive() const
{
	switch (slot)
	{
	case 0: glActiveTexture(GL_TEXTURE0); break;
	case 1: glActiveTexture(GL_TEXTURE1); break;
	case 2: glActiveTexture(GL_TEXTURE2); break;
	case 3: glActiveTexture(GL_TEXTURE3); break;
	case 4: glActiveTexture(GL_TEXTURE4); break;
	case 5: glActiveTexture(GL_TEXTURE5); break;
	case 6: glActiveTexture(GL_TEXTURE6); break;
	case 7: glActiveTexture(GL_TEXTURE7); break;
	case 8: glActiveTexture(GL_TEXTURE8); break;
	case 9: glActiveTexture(GL_TEXTURE9); break;
	case 10: glActiveTexture(GL_TEXTURE10); break;
	case 11: glActiveTexture(GL_TEXTURE11); break;
	case 12: glActiveTexture(GL_TEXTURE12); break;
	case 13: glActiveTexture(GL_TEXTURE13); break;
	case 14: glActiveTexture(GL_TEXTURE14); break;
	case 15: glActiveTexture(GL_TEXTURE15); break;
	default: glActiveTexture(GL_TEXTURE0); break;
	}
}

void Texture::textureFilter(GLint mag, GLint min)
{
	use();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
}

void Texture::textureWrap(GLint S, GLint T)
{
	use();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, T);
}

void Texture::use() const
{
	selectActive();
	glBindTexture(GL_TEXTURE_2D, ID);
}

unsigned int Texture::getSlot() const
{
	return slot;
}