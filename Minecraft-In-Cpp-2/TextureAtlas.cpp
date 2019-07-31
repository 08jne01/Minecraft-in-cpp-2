#include "TextureAtlas.h"

TextureAtlas::TextureAtlas()

{

}

void TextureAtlas::readData(const std::string& filename)

{
	std::ifstream in(filename);
	std::string line;
	std::string data;

	int gatherData = 0;
	if (!in.is_open())

	{
		std::cout << "Failed to open texture database" << std::endl;
		std::string error;
		char arr[20];
		strerror_s(arr, errno);

		std::cout << "Error: " << arr << std::endl;
	}

	else

	{
		int dataOut[7];
		while (getline(in, line))

		{
			std::stringstream os(line);

			if (line.find('#') != std::string::npos)

			{
				gatherData = 0;
			}

			else

			{
				os >> dataOut[gatherData];
				gatherData++;
			}

			if (gatherData == 7)

			{
				BlockData block;
				block.ID = dataOut[0];
				block.texCoordsTop.x = dataOut[1];
				block.texCoordsTop.y = dataOut[2];
				block.texCoordsSide.x = dataOut[3];
				block.texCoordsSide.y = dataOut[4];
				block.texCoordsBottom.x = dataOut[5];
				block.texCoordsBottom.y = dataOut[6];
				blockData.push_back(block);
			}

		}

		in.close();
	}
}

void TextureAtlas::printData() const

{
	for (int i = 0; i < blockData.size(); i++)

	{
		std::cout << "Block ID: " << (int)blockData[i].ID << std::endl;
	}
}

TextureAtlas::BlockData TextureAtlas::fetchData(unsigned char id) const

{
	for (int i = 0; i < blockData.size(); i++)

	{
		if (blockData[i].ID == id) return blockData[i];
	}

	return BlockData(1);
}

glm::vec2 TextureAtlas::fetchCoords(unsigned char id, unsigned int face) const

{
	for (int i = 0; i < blockData.size(); i++)

	{
		if (blockData[i].ID == id)

		{
			switch (face)

			{
			case BACK:
				return blockData[i].texCoordsSide;
			case FRONT:
				return blockData[i].texCoordsSide;
			case LEFT:
				return blockData[i].texCoordsSide;
			case RIGHT:
				return blockData[i].texCoordsSide;
			case TOP:
				return blockData[i].texCoordsTop;
			case BOTTOM:
				return blockData[i].texCoordsBottom;
			}
		}
	}

	return glm::vec2(240, 240);
}