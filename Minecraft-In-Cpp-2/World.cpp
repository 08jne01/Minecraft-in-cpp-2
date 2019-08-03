#include "World.h"

World::World(): perlinNoise(100, 100, 23, 500.0, 0.5)

{
	/*for (int n = 0; n < sizeX; n++)

	{
		for (int m = 0; m < sizeZ; m++)

		{
			genChunk(n*16, m*16);
			
		}
	}*/

	//genChunk(0, 0);
}

void World::genChunk(int x, int z)

{
	std::vector<float> heightMap;
	getChunkHeightMap(heightMap, z, x);
	Chunk chunk(heightMap);
	chunk.coordinateData.position = glm::vec3(x, -100, z);
	chunks.push_back(chunk);
	updateAdjacentChunks(*chunks.end());
}

void World::removeChunk(int x, int z)

{
	for (std::list<Chunk>::iterator it = chunks.begin(); it != chunks.end(); it++)

	{
		glm::vec3 pos = it->coordinateData.position;
		int indexX = (int)pos.x / 16;
		int indexZ = (int)pos.z / 16;

		//std::cout << indexX << " " << indexZ << std::endl;

		if (indexX == (x / 16) && indexZ == (z / 16))

		{
			chunks.erase(it);
			break;
		}
	}
}

int World::checkNextToSpiral(const Point point) const

{
	int adjacent = 0;

	for (int i = 0; i < spiral.size(); i++)

	{
		if (!(point.x == spiral[i].x && point.y == spiral[i].y))

		{
			if (spiral[i].x == point.x && spiral[i].y == point.y + 1) adjacent++;
			if (spiral[i].x == point.x && spiral[i].y == point.y - 1) adjacent++;
			if (spiral[i].x == point.x + 1 && spiral[i].y == point.y) adjacent++;
			if (spiral[i].x == point.x - 1 && spiral[i].y == point.y) adjacent++;
		}
	}
	return adjacent;
}

void World::unloadChunks()

{
	for (std::list<Chunk>::iterator it = chunks.begin(); it != chunks.end(); it++)

	{
		if (!it->shouldLoad)

		{
			updateAdjacentChunks(*it);
			chunks.erase(it);
			break;
		}
	}
}

void World::getChunksShouldUnload(const Camera& camera)

{
	int posX = -(int)camera.cameraEntity.position.x;
	int posZ = -(int)camera.cameraEntity.position.z;

	for (std::list<Chunk>::iterator it = chunks.begin(); it != chunks.end(); it++)

	{
		int chunkX = (int)it->coordinateData.position.x;
		int chunkZ = (int)it->coordinateData.position.z;
		float dist = pow(posX - chunkX, 2) + pow(posZ - chunkZ, 2);
		if (dist > pow((sizeX/2 + 1)*16, 2) + pow((sizeZ/2 + 1)*16, 2))

		{
			it->shouldLoad = 0;
		}
	}
}

void World::getChunksShouldLoad(const Camera& camera)

{
	int posX = -(int)camera.cameraEntity.position.x/16;
	int posZ = -(int)camera.cameraEntity.position.z/16;

	for (int i = -sizeX/2; i <= sizeX/2; i++)

	{
		for (int k = -sizeZ / 2; k <= sizeZ/2; k++)

		{
			int alive = 0;
			for (std::list<Chunk>::iterator it = chunks.begin(); it != chunks.end(); it++)

			{
				if ((i + posX) * 16 == (int)it->coordinateData.position.x && (k + posZ) * 16 == (int)it->coordinateData.position.z)

				{
					alive = 1;
				}
			}

			if (!alive)

			{
				genChunk((i + posX) * 16, (k + posZ) * 16);
				return;
			}
		}
	}
}

void World::getChunkHeightMap(std::vector<float>& chunkHeight, float x, float z)

{
	for (int i = 0; i < 16; i++)

	{
		for (int k = 0; k < 16; k++)

		{
			float height = perlinNoise.fractalNoise(x + (float)i, z + (float)k, 20, 64.0);
			chunkHeight.push_back(100 + height);
			//std::cout << height << std::endl;
		}
	}
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
				if (posX == chunkposX && posZ - 16 == chunkposZ) chunk.plusZ = &*it;
				if (posX == chunkposX && posZ + 16 == chunkposZ) chunk.minusZ = &*it;
			}

			if (localPlusX != chunk.plusX || localMinusX != chunk.minusX || localPlusZ != chunk.plusZ || localMinusZ != chunk.minusZ)

			{
				return 1;
			}
		}
	}

	return 0;
}

void World::updateAllChunks()

{
	for (std::list<Chunk>::iterator it = chunks.begin(); it != chunks.end(); it++)

	{
		updateAdjacentChunks(*it);
	}
}

std::list<Chunk>& World::getChunksRef()

{
	return chunks;
}

void World::addChunk(const Chunk& chunk)

{
	chunks.push_back(chunk);
}