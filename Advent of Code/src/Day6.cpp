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
		int maxTime = _time[i], auxResult = 0;
		for (int v = 1; v < maxTime - 1; v++)
		{
			int distance = v * (maxTime - v);
			if (distance > _distance[i]) 
			{
				auxResult++;
			}
		}
		result *= auxResult;
	}
	return result;
}

