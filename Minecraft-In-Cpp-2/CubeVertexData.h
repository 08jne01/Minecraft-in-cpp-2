#pragma once
#include <vector>
#include "Vertex.h"

#define BACK 0
#define FRONT 1
#define LEFT 2
#define RIGHT 3
#define TOP 4
#define BOTTOM 5

struct CubeVertexData

{
	CubeVertexData()

	{

	}
	//CCW

	std::vector<std::vector<Vertex>> verticesFaces = 
	
	{
		//BACk
		{
			Vertex({-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}), //0 1 2, 2 1 3
			Vertex({0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}),
			Vertex({-0.5f,0.5f,-0.5f}, {1.0f, 0.0f}),
			Vertex({0.5f, 0.5f, -0.5f}, {0.0f, 0.0f}) 
		},
		//Front
		{
			Vertex({-0.5f, -0.5f, 0.5f}, {1.0f, 1.0f}), //0 1 2, 2 1 3 //Reverse
			Vertex({0.5f, -0.5f, 0.5f}, {0.0f, 1.0f}),
			Vertex({-0.5f,0.5f,0.5f}, {1.0f, 0.0f}),
			Vertex({0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}) 
		},
		//Left
		{
			Vertex({-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}), //0 1 3, 3 1 2
			Vertex({-0.5f, -0.5f, 0.5f}, {0.0f, 1.0f}),
			Vertex({-0.5f,0.5f,-0.5f}, {1.0f, 0.0f}),
			Vertex({-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}) 
		},
		//Right
		{
			Vertex({0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}), //0 1 2, 2 1 3
			Vertex({0.5f, -0.5f, 0.5f}, {0.0f, 1.0f}),
			Vertex({0.5f, 0.5f,-0.5f}, {1.0f, 0.0f}),
			Vertex({0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}) 
		},
		//Top
		{
			Vertex({-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f}), //0 1 2, 2 1 3
			Vertex({0.5f, 0.5f, -0.5f}, {0.0f, 1.0f}),
			Vertex({-0.5f,0.5f, 0.5f}, {1.0f, 0.0f}),
			Vertex({0.5f, 0.5f, 0.5f}, {0.0f, 0.0f})
		},
		//Bottom
		{
			Vertex({-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}), //0 3 2, 2 3 1
			Vertex({0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}),
			Vertex({-0.5f,-0.5f,0.5f}, {1.0f, 0.0f}),
			Vertex({0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}) 
		}
	};

	std::vector <std::vector<unsigned int>> indiciesFaces = 
	
	{
		{
			3, 1, 2,
			2, 1, 0
		},

		{
			0, 1, 2,
			2, 1, 3
		},

		{
			3, 2, 1,
			1, 2, 0
		},

		{
			3, 1, 2,
			2, 1, 0
		},

		{
			3, 1, 2,
			2, 1, 0
		},

		{
			3, 2, 1,
			1, 2, 0
		}
	};

};