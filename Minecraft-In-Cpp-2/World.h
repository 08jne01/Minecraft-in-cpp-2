#pragma once
#include <list>
#include <iostream>
#include "Chunk.h"
#include "PerlinNoise.h"
#include "Point.h"
#include "Camera.h"

class World

{
public:
	World();
	void getChunkHeightMap(std::vector<float>& chunkHeight, float x, float z);
	std::list<Chunk>& getChunksRef();
	void addChunk(const Chunk& chunk);
	int updateAdjacentChunks(Chunk& chunk);
	void genChunk(int x, int z);
	void removeChunk(int x, int z);
	void updateAllChunks();
	void unloadChunks();
	void getChunksShouldUnload(const Camera& camera);
	void getChunksShouldLoad(const Camera& camera);
private:
	PerlinNoise perlinNoise;
	std::list<Chunk> chunks;
	std::vector<Point> spiral;
	int checkNextToSpiral(const Point point) const;
	int sizeX = 12;
	int sizeZ = 12;
	int x, y;
};