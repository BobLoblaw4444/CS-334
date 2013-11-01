#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::string;

char*  fileName = new char(15);
float turnAngle;
int numOfIterations;
string initialLetter;

string expandRules(string startString);

class ruleObject
{
	public:
		char letter;
		float weight;
		string rule;

		ruleObject(char inLetter, float inWeight, string inRule)
		{
			letter = inLetter;
			weight = inWeight;
			rule = inRule;
		}
};

ruleObject* ruleArray[15];

int main()
{
	std::ifstream infile;
	infile.open("rules.txt");

	string line;
	int lineCount = 0;
	int i = 0;
	for (string line; std::getline(infile, line);)
	{
		if(lineCount == 1)
		{
			turnAngle = stof(line);
		}
		else if(lineCount == 2)
		{
			numOfIterations = stoi(line);
		}
		else if(lineCount == 3)
		{
			initialLetter = line[0];
		}
		else if(lineCount > 3)
		{
			if(strstr(line.c_str(), "end"))
			{
				lineCount++;
				continue;
			}
			char letter = line[0];
			unsigned pos = line.find(" -> ");
			string rule = line.substr(pos+4);
			ruleArray[i] = new ruleObject(letter, 1.0f, rule);
			//cout << ruleArray[i]->rule;
			i++;
		}
		lineCount++;
		//cout<<line <<std::endl;
	}
	
	string expandedRules = initialLetter;
	for(int i = 0; i < numOfIterations; i++)
	{
		expandedRules = expandRules(expandedRules);
	}
	cout <<expandedRules;
}

string expandRules(string startString)
{
	string resultString;
	for each(char letter in startString)
	{
		for(int i = 0; i < 1; i++)
		{
			if(letter == ruleArray[i]->letter)
			{
				//cout << ruleArray[i]->rule <<std::endl;
				resultString += ruleArray[i]->rule;
			}
			else
				resultString += letter;
		}
	}
	//cout<<resultString;
	return resultString;
}