#pragma once
#include <string>
#include <fstream>
#include <unordered_map>

class Day1
{
public:
	Day1(std::string filename);
	int FirstPuzzle();
	int SecondPuzzle();
	bool FindNumber(std::string posibleWordNumber, int* firstNumber, int* lastNumber);
private:
	std::string _filename;
	std::unordered_map<std::string, int> _wordToNumber = {
		{"one", 1},
		{"two", 2},
		{"three", 3},
		{"four", 4},
		{"five", 5},
		{"six", 6},
		{"seven", 7},
		{"eight", 8},
		{"nine", 9},
		{"1",1},
		{"2", 2},
		{"3", 3},
		{"4", 4},
		{"5", 5},
		{"6", 6},
		{"7", 7},
		{"8", 8},
		{"9", 9},
	};
};

