#include "Day3.h"
#include <iostream>

Day3::Day3(std::string filename) : _filename(filename)
{
}

int Day3::FirstPuzzle()
{
	std::ifstream ifs(_filename);
	int result = 0;
	//Two maps, one for special chars and another one for numbers
	std::vector<int> posChar = {};
	std::unordered_map<int, int> posAndNumber = {};
	while (!ifs.eof())
	{
		std::string line;
		std::getline(ifs, line);
		std::cout << line << std::endl;
		std::vector<int> posChar2 = {};
		std::unordered_map<int, int> posAndNumber2 = {};
		int value = 0, pos = 0;
		bool reset = false, toSum = false, leftNotPoint = false;
		for (auto it = line.begin(); it != line.end(); it++)
		{
			if (*it != '.')
			{
				if (isdigit(*it))
				{
					const char aux = *it;
					value = value * 10 + atoi(&aux);
					if (leftNotPoint)
					{
						toSum = true;
						leftNotPoint = false;
					}
					for (auto position : posChar)
					{
						if (std::abs(position - pos) <= 1)
						{
							toSum = true;
						}
					}
					reset = true;
				}
				else
				{
					if (reset)
					{
						result += value;
						value = 0;
						reset = false;
					}

					for (auto& pair : posAndNumber)
					{
						int firstPos = pair.first;
						if (pair.second > 999) {
							firstPos -= 3;
						}
						else if (pair.second > 99) {
							firstPos -= 2;
						}
						else if (pair.second > 9) {
							firstPos -= 1;
						}
						if (std::abs(pair.first - pos) <= 1 || std::abs(firstPos - pos) <= 1)
						{
							result += pair.second;
							pair.second=0;
						}

					}
					posChar2.push_back(pos);
					leftNotPoint = true;
				}
			}
			else if (reset)
			{
				if (toSum)
				{
					result += value;
					toSum = false;
				}
				else
				{
					posAndNumber2.insert({ pos - 1,value });
				}
				value = 0;
				reset = false;
			}
			else if (leftNotPoint)
			{
				leftNotPoint = false;
			}
			pos++;
		}
		if (reset)
		{
			if (toSum)
			{
				toSum = false;
				result += value;
			}
			else
			{
				posAndNumber2.insert({ pos - 1,value });
			}
		}
		posAndNumber = posAndNumber2;
		posChar = posChar2;
	}
	return result;
}
