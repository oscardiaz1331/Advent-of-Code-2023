#include "Day6.h"

Day6::Day6(std::string filename) :_filename(filename)
{
	std::ifstream ifs(_filename);
	while (!ifs.eof())
	{
		std::string line, word;
		std::getline(ifs, line);
		std::istringstream lineStream(line);
		lineStream >> word;
		std::vector<int> aux;
		while (!lineStream.eof())
		{
			int number;
			lineStream >> number;
			aux.push_back(number);
		}
		if (word == wordTime)
		{
			_time = aux;
		}
		else if (word == distanceWord)
		{
			_distance = aux;
		}
	}
}

int Day6::FirstPuzzle()
{
	int result = 1;
	for (int i = 0; i < _time.size(); i++)
	{
		double valueMin = std::trunc((_time[i] - sqrt(_time[i] * _time[i] - 4 * _distance[i])) / 2),
			valueMax = std::trunc((_time[i] + sqrt(_time[i] * _time[i] - 4 * _distance[i])) / 2),
			auxResult = valueMax - valueMin;
		result *= auxResult;
	}
	return result;
}

int Day6::LastPuzzle()
{
	double time = 0, distance = 0;
	for (int i = 0; i < _time.size(); i++)
	{
		time = time * pow(10, FindNDigits(_time[i])) + _time[i];
		distance = distance * pow(10, FindNDigits(_distance[i])) + _distance[i];
	}
	//The mathematic equation to calculate the distance is a Quadratic inequation, I calculate the minimum and maximum value and only loops in this values
	double valueMin = std::trunc((time - sqrt(time * time - 4 * distance)) / 2),
		valueMax = std::trunc((time + sqrt(time * time - 4 * distance)) / 2),
		result = valueMax - valueMin;
	
	return result;
}

int Day6::FindNDigits(int number)
{
	int nDigits = 0;
	while (number > pow(10, nDigits))
	{
		nDigits++;
	}
	return nDigits;
}
