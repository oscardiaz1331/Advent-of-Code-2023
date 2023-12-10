#include "Day3.h"

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
							pair.second = 0;
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

int Day3::LastPuzzle()
{
	std::ifstream ifs(_filename);
	int result = 0;
	//Two maps, one for special chars and another one for numbers
	std::vector<int> posChar1 = {}, posChar2 = {}, posChar3 = {};
	std::unordered_map<int, int> posAndNumber1 = {}, posAndNumber2 = {}, posAndNumber3 = {};
	int i = 0;
	while (!ifs.eof())
	{
		i++;
		std::string line;
		std::getline(ifs, line);
		int value = 0, pos = 0;
		bool reset = true;
		for (auto it = line.begin(); it != line.end(); it++)
		{
			if (*it != '.')
			{
				if (isdigit(*it))
				{
					const char aux = *it;
					value = value * 10 + atoi(&aux);
					reset = false;
				}
				else if (*it == gear)
				{
					reset = true;
					posChar3.push_back(pos);
				}
				else 
				{
					reset = true;
				}
			}
			else 
			{
				reset = true;
			}
			if (reset && value != 0)
			{
				posAndNumber3.insert({ pos - 1,value });
				value = 0;
			}
			pos++;
		}
		if (value != 0)
		{
			posAndNumber3.insert({ pos - 1,value });
		}
		for (auto& pos : posChar2) 
		{
			int nInGear = 0, firstNumber = 0, secondNumber = 0;
			for (auto& map : { posAndNumber1, posAndNumber2, posAndNumber3 }) 
			{
				for (auto& pair : map) 
				{
					if (NearPoisitions(pos, pair.first, pair.second))
					{
						if (nInGear == 0) {
							firstNumber = pair.second;
							nInGear++;
						}
						else if (nInGear == 1)
						{
							secondNumber = pair.second;
							nInGear++;

						}
						else {
							nInGear++;
							break;
						}
					}
				}
			}
			if (nInGear == 2) 
			{
				result += firstNumber * secondNumber;
			}
		}
		posAndNumber1 = posAndNumber2;
		posChar1 = posChar2;
		posAndNumber2 = posAndNumber3;
		posChar2 = posChar3;
		posAndNumber3.clear();
		posChar3.clear();
	}
	return result;
}

bool Day3::NearPoisitions(int charPos, int numberPos, int number)
{
	int firstPos = numberPos;
	if (number > 999) {
		firstPos -= 3;
	}
	else if (number > 99) {
		firstPos -= 2;
	}
	else if (number > 9) {
		firstPos -= 1;
	}
	if (std::abs(numberPos - charPos) <= 1 || std::abs(firstPos - charPos) <= 1)
	{
		return true;
	}
	return false;
}