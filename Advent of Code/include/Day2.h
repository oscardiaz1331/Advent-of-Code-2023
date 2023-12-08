#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>

class Day2
{
public:
	Day2(std::string filename);
	int FirstPuzzle();
	int LastPuzzle();
private:
	std::string _filename;
	std::unordered_map<std::string, int> _colorsAndMaxN = {
		{"red", 12},
		{"green", 13},
		{"blue", 14},
	};
};