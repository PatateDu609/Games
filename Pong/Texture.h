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

	bool load();
	void use() const;
	unsigned int getSlot() const;

	void textureFilter(GLint mag, GLint min);
	void textureWrap(GLint S, GLint T);

private:
	unsigned int ID;
	unsigned int slot;
	std::string file;
	int width;
	int height;
	int channels;

	void selectActive() const;
};

#endif // !TEXTURE_H