#include "TerrainGenerator.h"

TerrainGenerator::TerrainGenerator(void)
{
	vertexNum = 1;
	increment = .01f;
	heightAdjust = 9;

	worldHeight = 2;
	worldWidth = 2;
}

void TerrainGenerator::generateTerrain()
{
	SimplexNoise* sn = new SimplexNoise();
	srand(time(0));
	
	int rndOffset = rand()%255;

	for(float i = 0; i < worldHeight; i+=increment)
	{
		for(float j = 0; j < worldWidth; j+=increment)
		{
			heightAdjust = (float)(rand() % 1) + heightAdjust;

			float height = sn->noise(i+rndOffset,j+rndOffset)/heightAdjust;
			vertexString << "v " << i << " " << j << " " << height <<"\n";

			
			height = sn->noise(i+increment+rndOffset,j+rndOffset)/heightAdjust;
			vertexString << "v " << i+increment << " " << j << " " << height <<"\n";

			
			height = sn->noise(i+rndOffset,j+increment+rndOffset)/heightAdjust;
			vertexString << "v " << i << " " << j+increment << " " << height <<"\n";
			
			faceString << "f " << vertexNum << " " << vertexNum + 1 << " " << vertexNum + 2 <<"\n";
			faceString << "f " << vertexNum + 2 << " " << vertexNum + 1 << " " << vertexNum <<"\n";

			
			height = sn->noise(i+increment+rndOffset,j+increment+rndOffset)/heightAdjust;
			vertexString << "v " << i+increment << " " << j+increment << " " << height <<"\n";

			faceString << "f " << vertexNum + 1 << " " << vertexNum + 2 << " " << vertexNum + 3 <<"\n";
			faceString << "f " << vertexNum + 3 << " " << vertexNum + 2 << " " << vertexNum + 1 <<"\n";
			
			vertexNum+=4;
			/*if(val < -.25f)
				cout << "-";
			else if (val < -.5f)
				cout << "-";
			else if (val < -.75f)
				cout << "-";
			else if (val < 0)
				cout << "-";
			else if(val < .25f)
				cout << "+";
			else if (val < .5f)
				cout << "+";
			else if (val < .75f)
				cout << "+";
			else
				cout << "+";
		}
		cout <<endl;*/
		}
	}

	std::ofstream objfile;
	objfile.open ("../data-files/terrain.obj");
	objfile << vertexString.rdbuf();
	objfile << faceString.rdbuf();
	objfile.close();
}
