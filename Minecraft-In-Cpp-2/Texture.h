#pragma once
#include <stb/stb_image.h>
#include <glad/glad.h>
#include <string>
#include <vector>
struct TextureTypeException : public std::exception

{
	const char* what() const throw()

	{
		return "Invalid texture type exception!";
	}
};


class Texture

{
public:
	Texture(const std::string& path, unsigned int typeTex);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;
private:

	unsigned int renderID, type;
	std::string filePath;
	unsigned char* localBuffer;
	int width, height, bpp;
};