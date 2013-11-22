#include "SimplexNoise.h"
#include <iostream>
#include <sstream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::stringstream;

// Streams to write out the vertices and faces, then combine into obj later
stringstream vertexString;
stringstream faceString;

int vertexNum = 1;

int main()
{
	SimplexNoise* sn = new SimplexNoise();
	for(int i = 0; i < 20; i++)
	{
		for(int j = 0; j < 20; j++)
		{
			float height = sn->noise(i,j);
			vertexString << "v " << i << " " << j << " " << height <<"\n";

			height = sn->noise(i+1,j);
			vertexString << "v " << i+1 << " " << j << " " << height <<"\n";

			height = sn->noise(i,j+1);
			vertexString << "v " << i << " " << j+1 << " " << height <<"\n";
			
			faceString << "f " << vertexNum << " " << vertexNum + 1 << " " << vertexNum + 2 <<"\n";
			faceString << "f " << vertexNum + 2 << " " << vertexNum + 1 << " " << vertexNum <<"\n";

			height = sn->noise(i+1,j+1);
			vertexString << "v " << i+1 << " " << j+1 << " " << height <<"\n";

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