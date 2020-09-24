#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <glad/glad.h>

class Texture
{
public:
	Texture() = delete;

	Texture(unsigned int tex_slot, std::string filename, bool flip = false);
	Texture(unsigned int tex_slot, unsigned char* image, int w, int h, int nbrChannel);

	bool load(bool mipmap = true);
	void use() const;
	unsigned int getSlot() const;

	void textureFilter(GLint mag, GLint min);
	void textureWrap(GLint S, GLint T);

private:
	unsigned int ID;
	unsigned int slot;
	unsigned char* data;
	int width;
	int height;
	int channels;

	bool raw;

	void selectActive() const;
};

#endif // !TEXTURE_H