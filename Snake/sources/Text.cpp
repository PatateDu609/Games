#include "../headers/Text.h"
#include <glm/gtc/matrix_transform.hpp>

void Text::initVAO()
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 6, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Text::Text(Font face, std::string text) : font(face), content(text), VBO(0), VAO(0), scale(1.0f),
	coord(0.0f), color(0.0f), shader(NULL), proj(1.0f)
{
	initVAO();
}

Text::Text(Font face) : Text(face, "")
{

}

void Text::setContent(std::string text)
{
	content = text;
}

std::string Text::getContent() const
{
	return content;
}

void Text::setCoord(float x, float y)
{
	coord.x = x;
	coord.y = size.y - y;
	std::cout << "x (size.x = " << size.x << ") : " << x << std::endl; 
}

void Text::setCoord(glm::vec2 coord)
{
	setCoord(coord.x, coord.y);
}

void Text::setSize(glm::vec2 size)
{
	this->size = size;
}

void Text::setScale(float scale)
{
	this->scale = scale;
}

void Text::setColor(glm::ivec3 color)
{
	this->color.x = static_cast<float>(color.x) / 255.0f;
	this->color.y = static_cast<float>(color.y) / 255.0f;
	this->color.z = static_cast<float>(color.z) / 255.0f;
}

void Text::setShader(std::string vertexShader, std::string fragmentShader)
{
	if (shader)
		delete shader;
	shader = new Shader(vertexShader.c_str(), fragmentShader.c_str());
}

Shader* Text::getShader()
{
	return shader;
}

void Text::draw()
{
	float x = coord.x;
	shader->use();
	shader->setVec3("textColor", color);
	shader->setMat4("projection", proj);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	for (std::string::const_iterator it = content.begin(); it != content.end(); it++)
	{
		Character ch = font.getChar(*it);

		float xPos = x + ch.bearing.x * scale;
		float yPos = coord.y - (ch.size.y - ch.bearing.y) * scale;
		float w = ch.size.x * scale;
		float h = ch.size.y * scale;

		float vertices[6][4] = {
			{ xPos,		yPos + h,	0.0f, 0.0f },
			{ xPos,		yPos,		0.0f, 1.0f },
			{ xPos + w,	yPos,		1.0f, 1.0f },

			{ xPos,		yPos + h,	0.0f, 0.0f },
			{ xPos + w,	yPos,		1.0f, 1.0f },
			{ xPos + w,	yPos + h,	1.0f, 0.0f },
		};
		if (ch.texture)
			ch.texture->use();
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		x += (ch.advance >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::projection(glm::mat4& projection)
{
	proj = projection;
}
