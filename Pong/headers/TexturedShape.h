#ifndef TEXTUREDSHAPE_H
#define TEXTUREDSHAPE_H

#include "Shape2D.h"
#include "Texture.h"
#include <array>

class TexturedShape : public Shape2D
{
public:
	TexturedShape(Texture *texture);

	void addVertex(glm::vec3 coord, glm::vec2 texCoord);
	void addTexture(Texture *texture);

	void useTextures();

protected:
	virtual void vertexAttribConfig();
	virtual void optConfig();

private:
	std::array<Texture *, 16> textures;

	virtual void addVertex(glm::vec3 coord);
	virtual void addVertex(glm::vec3 coord, glm::vec3 color);
};

#endif // !TEXTUREDSHAPE_H
