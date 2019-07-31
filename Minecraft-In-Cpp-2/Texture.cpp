#include "Texture.h"
#include <iostream>
Texture::Texture(const std::string& path, unsigned int typeTex): filePath(path), type(typeTex), localBuffer(nullptr)

{
	glGenTextures(1, &renderID);
	if (type == GL_TEXTURE_2D)

	{
		localBuffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);
		glBindTexture(GL_TEXTURE_2D, renderID);
		glTexStorage2D(GL_TEXTURE_2D, 4, GL_RGBA8, width, height);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	else if (type == GL_TEXTURE_CUBE_MAP)

	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, renderID);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP);

		std::vector<std::string> paths = { "Resources/Textures/Side.png", "Resources/Textures/Side.png", "Resources/Textures/Top.png", "Resources/Textures/Bottom.png", "Resources/Textures/Side.png", "Resources/Textures/Side.png" };

		for (unsigned int i = 0; i < paths.size(); i++)

		{
			localBuffer = stbi_load(paths[i].c_str(), &width, &height, &bpp, 4);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
		}

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	else

	{
		throw TextureTypeException();
	}

	if (localBuffer) stbi_image_free(localBuffer);
}

Texture::~Texture()

{
	glDeleteTextures(1, &renderID);
}

void Texture::bind(unsigned int slot) const

{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(type, renderID);
}

void Texture::unbind() const

{
	glBindTexture(type, 0);
}