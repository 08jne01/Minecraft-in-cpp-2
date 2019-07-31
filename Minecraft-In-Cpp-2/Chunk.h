#pragma once
#include "CubeVertexData.h"
#include "Entity.h"
#include <vector>
#include <amprt.h>
class Chunk

{
public:
	std::vector<unsigned char> blocks;

	Chunk()

	{
		blocks.resize(16 * 256 * 16);
		std::fill(blocks.begin(), blocks.end(), 0);
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
				return getBlock(i, j + 1, k);
			}
		}
	}

	Entity coordinateData;
	Chunk* minusX = nullptr;
	Chunk* plusX = nullptr;
	Chunk* minusZ = nullptr;
	Chunk* plusZ = nullptr;
};