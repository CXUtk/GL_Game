#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader & shader)
{
	this->_shader = shader;
	initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::DrawSprite(Texture2D & texture, glm::vec2 position, glm::vec2 size, GLfloat rotation, glm::vec3 color)
{
	this->_shader.apply();
	glm::mat4 model;

	// ���з�����ָ��λ��
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::translate(model, glm::vec3(size.x * 0.5f, size.y * 0.5f, 0.0f));

	// ��ת��ΪZ�� ����˷��Ѿ���ʼ
	model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-size.x * 0.5f, -size.y * 0.5f, 0.0f));

	// �ı��С
	model = glm::scale(model, glm::vec3(size, 1.0f));

	this->_shader.setMat4("model", model);
	this->_shader.setVec3("spriteColor", color);

	texture.apply();

	glBindVertexArray(this->_quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
	GLuint VBO;

	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	// ������ɫ��������
	glGenVertexArrays(1, &this->_quadVAO);
	glGenBuffers(1, &VBO);

	// ȷ������������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->_quadVAO);
	glEnableVertexAttribArray(0);

	// ��vertices���������ת��Ϊvec4�Ž���ɫ��
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
