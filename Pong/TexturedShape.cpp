#include "TexturedShape.h"

TexturedShape::TexturedShape(Texture *texture) : Shape2D()
{
	for (int i = 0; i < 16; i++)
		textures[i] = NULL;

	textures[texture->getSlot()] = texture;
}

void TexturedShape::addVertex(glm::vec3 coord, glm::vec2 texCoord)
{
	vertexCount++;
	addVertex(coord);
	data.push_back(texCoord.x);
	data.push_back(texCoord.y);
}

void TexturedShape::vertexAttribConfig()
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
}

void TexturedShape::optConfig()
{
	shader->use();
	shader->useTexture("texture0", *textures[0]);
}

void TexturedShape::addTexture(Texture *texture)
{
	textures[texture->getSlot()] = texture;
}

void TexturedShape::addVertex(glm::vec3 coord)
{
	data.push_back(coord.x);
	data.push_back(coord.y);
	data.push_back(coord.z);
}

void TexturedShape::addVertex(glm::vec3 coord, glm::vec3 color)
{
	
}

void TexturedShape::useTextures()
{
	for (int i = 0; i < 16; i++)
		if (textures[i])
			textures[i]->use();
}
