#ifndef TEXT_H
#define TEXT_H

#include "Font.h"
#include "Shader.h"

class Text
{
public:
	Text(Font face, std::string text);
	Text(Font face);

	void setContent(std::string text);
	std::string getContent() const;
	void setCoord(float x, float y);
	void setCoord(glm::vec2 coord);
	void setSize(glm::vec2 coord);
	void setScale(float scale);
	void setColor(glm::ivec3 color);
	void setShader(std::string vertexShader, std::string fragmentShader);
	Shader* getShader();

	void draw();
	void projection(glm::mat4& projection);

private:
	typedef Font::Character Character;
	std::string content;
	Font font;
	glm::vec2 coord;
	glm::vec2 size;
	float scale;
	glm::vec3 color;
	Shader *shader;
	glm::mat4 proj;

	unsigned int VBO;
	unsigned int VAO;

	void initVAO();
};

#endif // !TEXT_H