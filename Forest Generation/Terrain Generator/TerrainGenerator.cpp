#include "TerrainGenerator.h"

TerrainGenerator::TerrainGenerator(void)
{
	// Initialize terrain generation parameters
	vertexNum = 1;
	scale = .025f;
	heightAdjust = 8*scale;

	waterLevel = -0.5/heightAdjust;

	worldHeight = 50;
	worldWidth = 50;
}

void TerrainGenerator::generateTerrain()
{
	SimplexNoise* sn = new SimplexNoise();

	// Seed random number generator
	srand(time(0));
	
	// Compute a random value to ensure the terrain is seeded differently each time
	int rndOffset = rand()%255;

	std::ofstream heightMap;
	heightMap.open ("../Data/heightmap.txt");
	heightMap <<waterLevel << "\n";

	// Build the terrain one row of squares at a time
	for(int i = 0; i < worldHeight; i++)
	{
		for(int j = 0; j < worldWidth; j++)
		{
			float totalHeight = 0;
			
			// Compute and save the indices for the noise function
			float xIndex = (i*scale)+rndOffset;
			float yIndex = (j*scale)+rndOffset;

			topLeft = vertexNum;
			bottomLeft = vertexNum + 1;
			topRight = vertexNum + 2;
			bottomRight = vertexNum + 3;

			// Get vertex at top left corner of square
			float height = sn->noise(xIndex,yIndex)/heightAdjust;
			totalHeight += height;
			vertexString << "v " << i << " " << j << " " << height <<"\n";
			textureString << "vt " << 0 << " " << 0 <<"\n";

			// Get vertex at bottom left corner of square
			height = sn->noise(xIndex+scale,yIndex)/heightAdjust;
			totalHeight += height;
			vertexString << "v " << i+1 << " " << j << " " << height <<"\n";
			textureString << "vt " << 1 << " " << 0 <<"\n";

			// Get vertex at top right of square
			height = sn->noise(xIndex,yIndex+scale)/heightAdjust;
			totalHeight += height;
			vertexString << "v " << i << " " << j+1 << " " << height <<"\n";
			textureString << "vt " << 0 << " " << 1 <<"\n";

			// Get vertex at bottom right corner of square
			height = sn->noise(xIndex+scale,yIndex+scale)/heightAdjust;
			totalHeight += height;
			vertexString << "v " << i+1 << " " << j+1 << " " << height <<"\n";
			textureString << "vt " << 1 << " " << 1 <<"\n";

			heightMap << totalHeight/4 <<" ";

			for(int k = 0; k < 12; k++)
			{
				if(k < 6)
				{
					if(totalHeight/4 < (k/6)-1)
					{
						faceString <<"usemtl grass" <<k <<"\n";
					}
				}
				else
				{
					if(totalHeight/4 < k/6)
					{
						faceString <<"usemtl grass" <<k <<"\n";
					}
				}
			}

			// Create triangle from the first 3 vertices
			faceString << "f " << topLeft << "/1 " << bottomLeft << "/2 " << topRight <<"/3" <<"\n";
			faceString << "f " << topRight << "/3 " << bottomLeft << "/2 " << topLeft <<"/1" << "\n";

			// Create triangle using new point to complete the square
			faceString << "f " << bottomLeft << "/2 " << topRight << "/3 " << bottomRight <<"/4" <<"\n";
			faceString << "f " << bottomRight << "/4 " << topRight << "/3 " << bottomLeft << "/2 " <<"\n";			

			if(i == 0)
			{
				lowestLeft = vertexNum + 4;
				lowestRight = vertexNum + 5;

				vertexString << "v " << i << " " << j << " " << -1/heightAdjust <<"\n";
				vertexString << "v " << i << " " << j+1 << " " << -1/heightAdjust <<"\n";

				// Create triangle from the first 3 vertices
				faceString << "f " << topLeft << " " << topRight << " " << lowestLeft <<"\n";
				faceString << "f " << lowestLeft << " " << topRight << " " << topLeft <<"\n";

				// Create triangle from the first 3 vertices
				faceString << "f " << topRight << " " << lowestLeft << " " << lowestRight <<"\n";
				faceString << "f " << lowestRight << " " << lowestLeft << " " << topRight <<"\n";

				vertexNum+=2;
				
			}
			if(i == worldHeight-1)
			{
				lowestLeft = vertexNum + 4;
				lowestRight = vertexNum + 5;

				vertexString << "v " << i+1 << " " << j << " " << -1/heightAdjust <<"\n";
				vertexString << "v " << i+1 << " " << j+1 << " " << -1/heightAdjust <<"\n";

				// Create triangle from the first 3 vertices
				faceString << "f " << bottomLeft << " " << bottomRight << " " << lowestLeft <<"\n";
				faceString << "f " << lowestLeft << " " << bottomRight << " " << bottomLeft <<"\n";

				// Create triangle from the first 3 vertices
				faceString << "f " << bottomRight << " " << lowestLeft << " " << lowestRight <<"\n";
				faceString << "f " << lowestRight << " " << lowestLeft << " " << bottomRight <<"\n";
			
				vertexNum+=2;
				
			}
			if(j == 0)
			{
				lowestLeft = vertexNum + 4;
				lowestRight = vertexNum + 5;

				vertexString << "v " << i << " " << j << " " << -1/heightAdjust <<"\n";
				vertexString << "v " << i+1 << " " << j << " " << -1/heightAdjust <<"\n";

				// Create triangle from the first 3 vertices
				faceString << "f " << topLeft << " " << bottomLeft << " " << lowestLeft <<"\n";
				faceString << "f " << lowestLeft << " " << bottomLeft << " " << topLeft <<"\n";

				// Create triangle from the first 3 vertices
				faceString << "f " << bottomLeft << " " << lowestLeft << " " << lowestRight <<"\n";
				faceString << "f " << lowestRight << " " << lowestLeft << " " << bottomLeft <<"\n";

				vertexNum+=2;
			}
			if(j == worldWidth-1)
			{
				lowestLeft = vertexNum + 4;
				lowestRight = vertexNum + 5;

				vertexString << "v " << i << " " << j+1 << " " << -1/heightAdjust <<"\n";
				vertexString << "v " << i+1 << " " << j+1 << " " << -1/heightAdjust <<"\n";

				// Create triangle from the first 3 vertices
				faceString << "f " << topRight << " " << bottomRight << " " << lowestLeft <<"\n";
				faceString << "f " << lowestLeft << " " << bottomRight << " " << topRight <<"\n";

				// Create triangle from the first 3 vertices
				faceString << "f " << bottomRight << " " << lowestLeft << " " << lowestRight <<"\n";
				faceString << "f " << lowestRight << " " << lowestLeft << " " << bottomRight <<"\n";
			
				vertexNum+=2;
			}	

			// Increment vertexNum so that the next square can be created
			vertexNum+=4;
		}

		heightMap <<"\n";
	}
	
	topLeft = vertexNum;
	bottomLeft = vertexNum + 1;
	topRight = vertexNum + 2;
	bottomRight = vertexNum + 3;

	faceString << "usemtl water\n";

	// Create the water
	vertexString << "v " << 0.01f << " " << 0.01f << " " << waterLevel <<"\n";
	vertexString << "v " << worldWidth-.01f << " " << 0.01f << " " << waterLevel <<"\n";
	vertexString << "v " << 0.01f << " " << worldHeight-.01f << " " << waterLevel <<"\n";

	faceString << "f " << topLeft << " " << bottomLeft << " " << topRight <<"\n";
	faceString << "f " << topRight << " " << bottomLeft << " " << topLeft <<"\n";

	vertexString << "v " << worldWidth-.01f << " " << worldHeight-.01f << " " << waterLevel <<"\n";
	faceString << "f " << bottomLeft << " " << topRight << " " << bottomRight <<"\n";
	faceString << "f " << bottomRight << " " << topRight << " " << bottomLeft <<"\n";

	vertexNum+=4;

	topLeft = vertexNum;
	bottomLeft = vertexNum + 1;
	topRight = vertexNum + 2;
	bottomRight = vertexNum + 3;
	
	// Create the bottom
	vertexString << "v " << 0.01f << " " << 0.01f << " " << -1.0f/heightAdjust <<"\n";
	vertexString << "v " << worldWidth-.01f << " " << 0.01f << " " << -1.0f/heightAdjust <<"\n";
	vertexString << "v " << 0.01f << " " << worldHeight-.01f << " " << -1.0f/heightAdjust <<"\n";

	faceString << "f " << topLeft << " " << bottomLeft << " " << topRight <<"\n";
	faceString << "f " << topRight << " " << bottomLeft << " " << topLeft <<"\n";

	vertexString << "v " << worldWidth-.01f << " " << worldHeight-.01f << " " << -1.0f/heightAdjust <<"\n";
	faceString << "f " << bottomLeft << " " << topRight << " " << bottomRight <<"\n";
	faceString << "f " << bottomRight << " " << topRight << " " << bottomLeft <<"\n";

	vertexNum+=4;

	// Build an obj file from the vertices and faces lists
	std::ofstream objfile;
	objfile.open ("../Data/terrain.obj");
	objfile << "mtllib terrain.mtl\n";
	objfile << vertexString.rdbuf();
	objfile << textureString.rdbuf();
	objfile << faceString.rdbuf();
	objfile.close();

	heightMap.close();
}