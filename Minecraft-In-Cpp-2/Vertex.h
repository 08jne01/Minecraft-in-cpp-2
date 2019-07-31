#pragma once
#include <glm/ext.hpp>

struct Vertex

{
	Vertex(glm::vec3 position_, glm::vec2 textureCoords_):
		position(position_), textureCoords(textureCoords_)

	{

	}

	glm::vec3 position;
	glm::vec2 textureCoords;
};