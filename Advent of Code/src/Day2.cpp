#include "Day2.h"

Day2::Day2(std::string filename) : _filename(filename)
{
}

int Day2::FirstPuzzle()
{
	std::ifstream ifs(_filename);
	int result = 0;
	for (std::string line; std::getline(ifs, line);)
	{
		std::istringstream lineStream(line);
		std::string lineInfo;
		std::getline(lineStream, lineInfo, ':');
		int offset = line.find(' ');
		std::string char2Int = lineInfo.substr(offset);
		int id = std::stoi(char2Int);
		bool correct = true;
		std::cout << line << std::endl;
		for (std::string game; std::getline(lineStream, game, ';');)
		{
			if (correct) {
				std::istringstream gameStream(game);
				for (std::string cube; std::getline(gameStream, cube, ',');)
				{
					cube.erase(0, 1);
					offset = cube.find(' ');
					int number = std::stoi(cube);
					for (auto& pair : _colorsAndMaxN)
					{
						int pos = cube.find(pair.first);
						if (pos >= 0 && number > pair.second)
						{
							correct = false;
						}
					}
				}
			}
		}
		if (correct)
		{
			result += id;
			std::cout << "correct" << std::endl;
		}
	}
	return result;
}

int Day2::LastPuzzle()
{
	std::ifstream ifs(_filename);
	int result = 0;
	for (std::string line; std::getline(ifs, line);)
	{
		std::istringstream lineStream(line);
		std::string lineInfo;
		std::getline(lineStream, lineInfo, ':');
		int offset = line.find(' ');
		std::string char2Int = lineInfo.substr(offset);
		int id = std::stoi(char2Int);
		std::unordered_map<std::string, int> colorsAndNumbers = {
		{"red", 0},
		{"green", 0},
		{"blue", 0},
		};
		for (std::string game; std::getline(lineStream, game, ';');)
		{
			std::istringstream gameStream(game);
			for (std::string cube; std::getline(gameStream, cube, ',');)
			{
				cube.erase(0, 1);
				offset = cube.find(' ');
				int number = std::stoi(cube);
				for (auto& pair : colorsAndNumbers)
				{
					int pos = cube.find(pair.first);
					if (pos >= 0 && number > pair.second)
					{
						pair.second = number;
					}
				}
			}
		}
		int value = 1;
		for (auto& pair : colorsAndNumbers)
		{
			value *= pair.second;
		}
		result += value;
	}
	return result;
}
