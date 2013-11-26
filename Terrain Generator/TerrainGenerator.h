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
	stringstream faceString;

	// Counter to keep track of which vertex program is looking at
	int vertexNum;
	float increment;
	float heightAdjust;

	float worldHeight;
	float worldWidth;

	TerrainGenerator(void);
	~TerrainGenerator(void);
	void generateTerrain();
};

