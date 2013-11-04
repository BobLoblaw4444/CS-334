#include <iostream>
#include <string>
#include <fstream>
#include <list>

using std::cout;
using std::string;
using std::list;

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

bool count = false;
int fCount = 0;

float turnAngle;
int numOfIterations;
string initialString;
list<ruleObject*> ruleList;

void parseInput();
string expandRules(string startString);
string determineStochasticRule(char letter);
bool compareWeights(ruleObject* first, ruleObject* second);

int main()
{
	parseInput();
		// Expand the initial string using the rules for the given number of iterations
	string expandedRules = initialString;
	for(int i = 0; i < numOfIterations; i++)
	{
		if(i == numOfIterations-1)
			count = true;
		expandedRules = expandRules(expandedRules);
	}

	// Output final string to console
	cout <<expandedRules;
	cout << fCount;

	// Create tree.txt containing the string
	std::ofstream outfile;
	outfile.open ("tree.txt");
	outfile << expandedRules;
	outfile.close();
}

void parseInput()
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
			initialString = line[0];
		}
		else if(lineCount > 3)
		{
			if(strstr(line.c_str(), "end"))
			{
				lineCount++;
				continue;
			}
			// Default the weight to 1 and save the letter corresponding to the rule
			float weight = 1.0f;
			char letter = line[0];

			// Check if this rule has a weight, if so process it
			unsigned pos = 0;
			pos = line.find("(");
			if(pos < line.length())
			{
				// Find position of parenteheses so the weight can be collected from in between them
				int first = pos;
				int last = line.find(")");
				
				// There isn't a closed parenthese, abandon everything
				if(last > line.length())
				{
					cout << "Invalid input!";
					exit(1);
				}
				// Save the weight of this rule
				weight = stof(line.substr(first+1, last - first - 1));
			}
			// Locate the arrow and save the rest of the string as the rule
			pos = line.find(" -> ");
			string rule = line.substr(pos+4);
			ruleList.push_front(new ruleObject(letter, weight, rule));
			i++;
		}
		lineCount++;
	}
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
				resultString += determineStochasticRule(letter);
				foundInRules = true;
				if(count)
					fCount+=5;
				break;
			}
		}
		if(!foundInRules)
		{
			resultString += letter;
		}
		else
		{
			foundInRules = false;
		}
	}
	return resultString;
}

bool compareWeights(ruleObject* first, ruleObject* second)
{
	if(first->weight > second->weight)
	{
		return true;
	}
	else
		return false;
}

string determineStochasticRule(char letter)
{
	list<ruleObject*> rules;

	for(list<ruleObject*>::iterator it = ruleList.begin(); it != ruleList.end(); it++)
	{
		if(letter == (*it)->letter)
		{
			rules.push_front(*it);
		}
	}
	if(rules.size() == 1)
	{
		return rules.front()->rule;
	}

	rules.sort(compareWeights);
	for(list<ruleObject*>::iterator it = rules.begin(); it != rules.end(); it++)
	{
		//cout << (*it)->weight;
	}

	return rules.front()->rule;
}