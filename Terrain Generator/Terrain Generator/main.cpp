#include "SimplexNoise.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	SimplexNoise* sn = new SimplexNoise();
	for(float i = 0; i < 5; i+=.1f)
	{
		for(float j = 0; j < 7; j+=.1f)
		{
			float val = sn->noise(i,j);
			if(val < -.25f)
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
		cout <<endl;
	}
	int i;
	cin >> i;
}