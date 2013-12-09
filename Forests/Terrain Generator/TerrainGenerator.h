#pragma once
#include "SimplexNoise.h"

#include <time.h>
#include <sstream>
#include <fstream>
#include <iostream>

using std::stringstream;

class TerrainGenerator
{
public:
	// Streams to write out the vertices and faces, then combine into obj later
	stringstream vertexString;
	stringstream textureString;
	stringstream faceString;

	// Counter to keep track of which vertex program is looking at
	int vertexNum;
	int topLeft, bottomLeft, topRight, bottomRight, lowestLeft, lowestRight;

	float scale;
	float heightAdjust;
	float waterLevel;

	int worldHeight;
	int worldWidth;

	TerrainGenerator(void);
	~TerrainGenerator(void);
	void generateTerrain();
};

