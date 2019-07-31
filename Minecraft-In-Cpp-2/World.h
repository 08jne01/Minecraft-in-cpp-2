#pragma once
#include <list>
#include "Chunk.h"
#include "PerlinNoise.h"

class World

{
public:
	World();
	void getChunkHeightMap(std::vector<float>& chunkHeight, float x, float z);
	int updateAdjacentChunks(Chunk& chunk);
private:
	PerlinNoise perlinNoise;
	std::list<Chunk> chunks;
};