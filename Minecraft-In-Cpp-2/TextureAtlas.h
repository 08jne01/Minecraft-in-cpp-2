#pragma once
#include <sstream>
#include <fstream>
#include <iostream>
#include <glm/ext.hpp>
#include <vector>
#include "CubeVertexData.h"

class TextureAtlas

{
public:

	TextureAtlas();
	void readData(const std::string& filename);

	struct BlockData

	{
		BlockData(int defaultBlock = 0)

		{
			if (defaultBlock)

			{
				ID = 254;
				texCoordsTop = { 240, 240 };
				texCoordsSide = { 240, 240 };
				texCoordsBottom = { 240, 240 };
			}
		}

		glm::vec2 texCoordsTop;
		glm::vec2 texCoordsSide;
		glm::vec2 texCoordsBottom;
		unsigned char ID;
	};

	BlockData fetchData(unsigned char id) const;
	glm::vec2 fetchCoords(unsigned char id, unsigned int face) const;
	void printData() const;

private:
	std::vector<BlockData> blockData;
};