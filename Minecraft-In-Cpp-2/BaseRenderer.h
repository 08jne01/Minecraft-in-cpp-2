#pragma once
#include <vector>
#include "Vertex.h"
#include "Texture.h"
#include "Matrix.h"

class BaseRenderer

{
public:
	BaseRenderer();
	~BaseRenderer();

	void makeBuffers();
	void updateBuffers(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
	void setUniforms(const Entity& entity, const Camera& camera);
	void draw(Texture& texture, unsigned int indicesSize);

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	unsigned int shaderProgram;

	Config config;
};