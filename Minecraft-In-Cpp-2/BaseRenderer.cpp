#include "BaseRenderer.h"
#include <iostream>
BaseRenderer::BaseRenderer()

{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

BaseRenderer::~BaseRenderer()

{
	glDeleteBuffers(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}

void BaseRenderer::makeBuffers()

{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);
}

void BaseRenderer::setUniforms(const Entity& entity, const Camera& camera)

{
	//int color = glGetUniformLocation(shaderProgram, "u_color");
	//glUniform4f(color, 0.2, 0.1, 0.3, 1.0);

	int texF = glGetUniformLocation(shaderProgram, "u_texture");
	glUniform1i(texF, 0);

	int proj = glGetUniformLocation(shaderProgram, "projMatrix");
	glm::mat4 projMat = makeProjectionMatrix(config);
	glUniformMatrix4fv(proj, 1, GL_FALSE, &projMat[0][0]);

	int view = glGetUniformLocation(shaderProgram, "viewMatrix");
	glm::mat4 viewMat = makeViewMatrix(camera);
	glUniformMatrix4fv(view, 1, GL_FALSE, &viewMat[0][0]);

	int model = glGetUniformLocation(shaderProgram, "modelMatrix");
	glm::mat4 modelMat = makeModelMatrix(entity);
	glUniformMatrix4fv(model, 1, GL_FALSE, &modelMat[0][0]);
}

void BaseRenderer::updateBuffers(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)

{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)offsetof(Vertex, textureCoords));
	glEnableVertexAttribArray(1);
}

void BaseRenderer::draw(Texture& texture, unsigned int indicesSize)

{
	texture.bind();
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	texture.unbind();
}