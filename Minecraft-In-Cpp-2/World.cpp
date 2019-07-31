#include "World.h"

World::World(): perlinNoise(100, 100, 23, 100.0, 0.5)

{

}

void World::getChunkHeightMap(std::vector<float>& chunkHeight, float x, float z)

{

}

int World::updateAdjacentChunks(Chunk& chunk)

{
	if (chunk.plusX == nullptr || chunk.minusX == nullptr || chunk.plusZ == nullptr || chunk.minusZ == nullptr)

	{
		Chunk* localPlusX = chunk.plusX;
		Chunk* localMinusX = chunk.minusX;
		Chunk* localPlusZ = chunk.plusZ;
		Chunk* localMinusZ = chunk.minusZ;

		for (std::list<Chunk>::iterator it = chunks.begin(); it != chunks.end(); it++)

		{
			int posX = (int)it->coordinateData.position.x;
			int posZ = (int)it->coordinateData.position.z;

			int chunkposX = (int)chunk.coordinateData.position.x;
			int chunkposZ = (int)chunk.coordinateData.position.z;

			if (!(posX == chunkposX && posZ == chunkposZ))

			{
				if (posX == chunkposX + 16 && posZ == chunkposZ) chunk.plusX = &*it;
				if (posX == chunkposX - 16 && posZ == chunkposZ) chunk.minusX = &*it;
				if (posX == chunkposX && posZ + 16 == chunkposZ) chunk.plusZ = &*it;
				if (posX == chunkposX && posZ - 16 == chunkposZ) chunk.minusZ = &*it;
			}

			if (localPlusX != chunk.plusX || localMinusX != chunk.minusX || localPlusZ != chunk.plusZ || localMinusZ != chunk.minusZ)

			{
				return 1;
			}
		}
	}

	return 0;
}