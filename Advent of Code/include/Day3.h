#pragma once
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>

class Day3
{
private: 
	std::string _filename;
	char gear = '*';
public: 
	Day3(std::string filename);
	int FirstPuzzle();
	int LastPuzzle();
	bool NearPoisitions(int charPos, int numberPos, int number);
};

