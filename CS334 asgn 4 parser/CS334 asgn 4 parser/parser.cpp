#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <list>

using std::cout;
using std::string;
using std::list;

bool count = false;
int fCount = 0;

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

list<ruleObject*> ruleList;
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
			initialLetter = line;
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
			//ruleArray[i] = new ruleObject(letter, 1.0f, rule);
			ruleList.push_front(new ruleObject(letter, 1.0f, rule));
			i++;
		}
		lineCount++;
	}
	
	string expandedRules = initialLetter;
	for(int i = 0; i < numOfIterations; i++)
	{
		if(i == numOfIterations-1)
			count = true;
		expandedRules = expandRules(expandedRules);
	}
	cout <<expandedRules <<std::endl;
	cout << fCount;
}

string expandRules(string startString)
{
	string resultString;
	bool foundInRules = false;

	for each(char letter in startString)
	{
		for(list<ruleObject*>::iterator it = ruleList.begin(); it != ruleList.end(); it++)
		{
			if(letter == (*it)->letter)
			{
				//cout << ruleArray[i]->rule <<std::endl;
				resultString += (*it)->rule;
				foundInRules = true;
				if(count)
					fCount+=5;
			}
		}
		if(!foundInRules)
		{
			resultString += letter;
		}
		else
			foundInRules = false;
	}
	//cout<<resultString;
	return resultString;
}