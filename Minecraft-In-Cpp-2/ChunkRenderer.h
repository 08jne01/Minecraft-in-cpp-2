#pragma once
#include <list>
#include "BaseRenderer.h"
#include "Chunk.h"
#include "TextureAtlas.h"
#include "Texture.h"
#include "GeneralMaths.h"
#include "CubeVertexData.h"
#include "World.h"
class ChunkRenderer : public BaseRenderer

{
public:
	ChunkRenderer(unsigned int shaderProgram_, Config config_);
	~ChunkRenderer();
	void buildMesh(Chunk& chunk);
	void addVertices(Chunk& chunk, int i, int j, int k, int face, int index);
	void translateCubeMesh(const Chunk& chunk, int i, int j, int k, int index, int face, std::vector<Vertex>& vertexData, std::vector<unsigned int>& indexData);
	void drawChunk(const Chunk& chunk, const Camera& camera);
	void drawWorld(World& world, const Camera& camera);
private:
	TextureAtlas textureAtlas;
	Texture texture;
	unsigned int indexIndices = 0;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	CubeVertexData cube;

	std::vector<Vertex> vertexData;
	std::vector<unsigned int> indexData;
};