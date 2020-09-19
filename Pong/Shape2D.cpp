#include "Shape2D.h"

Shape2D::Shape2D(GLenum mode) : VAO(0), VBO(0), shader(NULL),
	data(), configured(false), vertexCount(0), usage(mode),
	_model(1.0f), _projection(1.0f)
{

}

Shape2D::~Shape2D()
{
	/*delete shader;
	shader = NULL;*/
}

void Shape2D::addVertex(glm::vec3 coord)
{
	vertexCount++;
	data.push_back(coord.x);
	data.push_back(coord.y);
	data.push_back(coord.z);
	data.push_back(0.64f);
	data.push_back(0.44f);
	data.push_back(0.91f);
}

void Shape2D::addVertex(glm::vec3 coord, glm::ivec3 color)
{
	vertexCount++;
	data.push_back(coord.x);
	data.push_back(coord.y);
	data.push_back(coord.z);
	data.push_back(color.x / 255.0f);
	data.push_back(color.y / 255.0f);
	data.push_back(color.z / 255.0f);
}

void Shape2D::config()
{
	if (configured)
		return;
	configured = true;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	float* raw = data.data();

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), raw, usage);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Shape2D::draw()
{
	if (!shader || !configured)
		std::cerr << "Error : Shape2D : Shader or Shape unitialized" << std::endl;
	glBindVertexArray(VAO);
	shader->use();
	shader->setMat4("projection", _projection);
	shader->setMat4("model", _model);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void Shape2D::setShader(std::string vertexShader, std::string fragmentShader)
{
	if (shader)
		delete shader;
	shader = new Shader(vertexShader.c_str(), fragmentShader.c_str());
}

void Shape2D::model(glm::mat4& model)
{
	_model = model;
}
void Shape2D::projection(glm::mat4& projection)
{
	_projection = projection;
}
