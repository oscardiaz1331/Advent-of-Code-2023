#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm>

class Day5
{
private:
	std::vector<double> seeds;
	std::vector<std::vector<std::tuple<double, double, double>>> transformations;//a vector which contains the maps, each map is another vector of tuples
	std::string _filename;
public:
	Day5(std::string filename);
	int FirstPuzzle();
	int LastPuzzle();
	void ReadInfo();
};

