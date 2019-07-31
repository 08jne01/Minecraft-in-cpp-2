#include "ChunkRenderer.h"

ChunkRenderer::ChunkRenderer(unsigned int shaderProgram_, Config config_): texture("Resources/Textures/Blocks.png", GL_TEXTURE_2D)

{
	shaderProgram = shaderProgram_;
	textureAtlas.readData("Resources/Database/BlocksTextureMap.dat");
	config = config_;
	makeBuffers();
}

ChunkRenderer::~ChunkRenderer()

{
	
}

void ChunkRenderer::buildMesh(const Chunk& chunk)

{
	vertices.clear();
	indices.clear();
	indexIndices = 0;

	for (int i = 0; i < 16; i++)

	{
		for (int j = 0; j < 256; j++)

		{
			for (int k = 0; k < 16; k++)

			{
				if (chunk.getBlock(i, j, k) != 0)

				{
					unsigned char block = chunk.getBlock(i, j, k);
					unsigned char back = chunk.adjacent(BACK, i, j, k);
					unsigned char front = chunk.adjacent(FRONT, i, j, k);
					unsigned char left = chunk.adjacent(LEFT, i, j, k);
					unsigned char right = chunk.adjacent(RIGHT, i, j, k);
					unsigned char top = chunk.adjacent(TOP, i, j, k);
					unsigned char bottom = chunk.adjacent(BOTTOM, i, j, k);

					if (back == 0) addVertices(chunk, i, j, k, BACK, indexIndices);
					if (front == 0) addVertices(chunk, i, j, k, FRONT, indexIndices);
					if (left == 0) addVertices(chunk, i, j, k, LEFT, indexIndices);
					if (right == 0) addVertices(chunk, i, j, k, RIGHT, indexIndices);
					if (top == 0) addVertices(chunk, i, j, k, TOP, indexIndices);
					if (bottom == 0) addVertices(chunk, i, j, k, BOTTOM, indexIndices);

					if (back == 5 && block != 5) addVertices(chunk, i, j, k, BACK, indexIndices);
					if (front == 5 && block != 5) addVertices(chunk, i, j, k, FRONT, indexIndices);
					if (left == 5 && block != 5) addVertices(chunk, i, j, k, LEFT, indexIndices);
					if (right == 5 && block != 5) addVertices(chunk, i, j, k, RIGHT, indexIndices);
					if (top == 5 && block != 5) addVertices(chunk, i, j, k, TOP, indexIndices);
					if (bottom == 5 && block != 5) addVertices(chunk, i, j, k, BOTTOM, indexIndices);
				}
			}
		}
	}
	updateBuffers(vertices, indices);
}

void ChunkRenderer::addVertices(const Chunk& chunk, int i, int j, int k, int face, int index)

{
	
	CubeVertexData cube;
	std::vector<Vertex> vertexData = cube.verticesFaces[face];
	std::vector<unsigned int> indexData = cube.indiciesFaces[face];

	translateCubeMesh(chunk, i, j, k, index, face, vertexData, indexData);

	for (int n = 0; n < vertexData.size(); n++)

	{
		vertices.push_back(vertexData[n]);
	}

	for (int n = 0; n < indexData.size(); n++)

	{
		indices.push_back(indexData[n]);
	}
	indexIndices += 4;
}

void ChunkRenderer::translateCubeMesh(const Chunk& chunk, int i, int j, int k, int index, int face, std::vector<Vertex>& vertexData, std::vector<unsigned int>& indexData)

{
	for (int n = 0; n < vertexData.size(); n++)

	{
		Vertex v = vertexData[n];
		glm::vec2 tex = textureAtlas.fetchCoords(chunk.getBlock(i, j, k), face);
		glm::vec2 def = v.textureCoords;
		//std::cout << def.x << " " << def.y << std::endl;
		float x, y;
		x = def.x / 16.0 + ((float)tex.x / 16.0) / 16.0;
		y = def.y / 16.0 + ((float)tex.y / 16.0) / 16.0;
		vertexData[n] = Vertex({ v.position.x + i, v.position.y + j, v.position.z + k }, { x,y });
	}

	offsetVector<unsigned int>(indexData, index);
}

void ChunkRenderer::drawChunk(const Chunk& chunk, const Camera& camera)

{
	setUniforms(chunk.coordinateData, camera);
	draw(texture, indices.size());
}