#pragma once
#include "CubeVertexData.h"
#include "Entity.h"
#include "BufferID.h"
#include <glad/glad.h>
#include <vector>
#include <iostream>
class Chunk

{
public:
	std::vector<unsigned char> blocks;

	Chunk()

	{
		blocks.resize(16 * 256 * 16);
		std::fill(blocks.begin(), blocks.end(), 0);
	}

	Chunk(std::vector<float>& heightMap)

	{
		blocks.resize(16 * 256 * 16);
		std::fill(blocks.begin(), blocks.end(), 0);

		/*for (int i = 0; i < 16; i++)

		{
			for (int k = 0; k < 16; k++)

			{
				int height = heightMap[i + k * 16];
				if (height > 0 && height < 256) setBlock(i, height, k, 1);
			}
		}*/

		for (int i = 0; i < 16; i++)

		{
			for (int j = 0; j < 256; j++)

			{
				for (int k = 0; k < 16; k++)

				{

					int height = heightMap[i + k * 16];
					
					if (j < height - 2)

					{
						setBlock(i, j, k, 3);
					}

					else if (j < height - 1)

					{
						setBlock(i, j, k, 2);
					}

					else if (j < height)

					{
						setBlock(i, j, k, 1);
					}
				}
			}
		}

		for (int i = 0; i < 16; i++)

		{
			for (int j = 0; j < 85; j++)

			{
				for (int k = 0; k < 16; k++)

				{
					if (getBlock(i, j, k) == 0)

					{
						setBlock(i, j, k, 5);
					}
				}
			}
		}

		for (int i = 0; i < 16; i++)

		{
			for (int j = 0; j < 256; j++)

			{
				for (int k = 0; k < 16; k++)

				{
					if (getBlock(i, j, k) == 5)

					{
						//if (adjacent(BACK, i, j, k) == 1) setBlock(i, j, k - 1, 4);
						//if (adjacent(FRONT, i, j, k) == 1) setBlock(i, j, k + 1, 4);
						//if (adjacent(LEFT, i, j, k) == 1) setBlock(i - 1, j, k, 4);
						//if (adjacent(RIGHT, i, j, k) == 1) setBlock(i + 1, j, k, 4);
						//std::cout << +adjacent(BOTTOM, i, j, k);
						if (adjacent(BOTTOM, i, j, k) == 1) setBlock(i, j - 1, k, 4);
					}
				}
			}
		}
	}

	~Chunk()

	{
		if (minusX != nullptr) minusX->plusX = nullptr;
		if (plusX != nullptr) plusX->minusX = nullptr;
		if (minusZ != nullptr) minusZ->plusZ = nullptr;
		if (plusZ != nullptr) plusZ->minusZ = nullptr;

		glDeleteBuffers(1, &this->bufferID.VAO);
		glDeleteBuffers(1, &this->bufferID.VBO);
		glDeleteBuffers(1, &this->bufferID.EBO);
	}

	void setBlock(int i, int j, int k, unsigned char type)

	{
		blocks[i + 256 * j + 16 * k] = type;
	}

	unsigned char getBlock(int i, int j, int k) const

	{
		return blocks[i + 256 * j + 16 * k];
	}

	unsigned char adjacent(int face, int i, int j, int k) const

	{
		switch (face)

		{
			case LEFT:

			{
				if (i - 1 < 0 && minusX == nullptr) return 0;
				else if (i - 1 < 0) return minusX->getBlock(15, j, k);
				return getBlock(i - 1, j, k);
			}

			case RIGHT:

			{
				if (i + 1 > 15 && plusX == nullptr) return 0;
				else if (i + 1 > 15) return plusX->getBlock(0, j, k);
				return getBlock(i + 1, j, k);
			}

			case BACK:

			{
				if (k - 1 < 0 && minusZ == nullptr) return 0;
				else if (k - 1 < 0) return minusZ->getBlock(i, j, 15);
				return getBlock(i, j, k - 1);
			}

			case FRONT:

			{
				if (k + 1 > 15 && plusZ == nullptr) return 0;
				else if (k + 1 > 15) return plusZ->getBlock(i, j, 0);
				return getBlock(i, j, k + 1);
			}

			case TOP:

			{
				if (j + 1 > 255) return 0;
				return getBlock(i, j + 1, k);
			}

			case BOTTOM:

			{
				if (j - 1 < 0) return 0;
				return getBlock(i, j - 1, k);
			}
		}
	}

	Entity coordinateData;
	Chunk* minusX = nullptr;
	Chunk* plusX = nullptr;
	Chunk* minusZ = nullptr;
	Chunk* plusZ = nullptr;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	BufferID bufferID;

	int shouldLoad = 1;
};