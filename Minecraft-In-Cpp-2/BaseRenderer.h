#pragma once
#include <vector>
#include "Vertex.h"
#include "Texture.h"
#include "Matrix.h"
#include "BufferID.h"

class BaseRenderer

{
public:
	BaseRenderer();
	~BaseRenderer();

	void makeBuffers(BufferID& buffersID);
	void updateBuffers(const BufferID& buffer, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	void setUniforms(const Entity& entity, const Camera& camera);
	void draw(const BufferID& buffer, Texture& texture, unsigned int indicesSize);

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	unsigned int shaderProgram;

	Config config;
};