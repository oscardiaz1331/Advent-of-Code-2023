#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class Day6
{
private:
	std::string _filename, wordTime = "Time:", distanceWord = "Distance:";
	std::vector<int> _time, _distance;
public:
	Day6(std::string filename);
	int FirstPuzzle();

};

