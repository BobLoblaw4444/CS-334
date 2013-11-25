#include "SimplexNoise.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>

using std::cout;
using std::cin;
using std::endl;
using std::stringstream;

// Streams to write out the vertices and faces, then combine into obj later
stringstream vertexString;
stringstream faceString;

int vertexNum = 1;
float increment = .025f;
int heightAdjust = 5;

int worldHeight = 5;
int worldWidth = 5;

int main()
{
	SimplexNoise* sn = new SimplexNoise();
	srand(0);
	float rndOffset = (float)(rand()%10);

	for(float i = 0; i < worldHeight; i+=increment)
	{
		for(float j = 0; j < worldWidth; j+=increment)
		{
			//heightAdjust = (rand() % 1);
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
	objfile.open ("terrain.obj");
	objfile << vertexString.rdbuf();
	objfile << faceString.rdbuf();
	objfile.close();

	/*int i;
	cin >> i;*/
}