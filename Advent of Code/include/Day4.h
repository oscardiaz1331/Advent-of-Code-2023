#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

class Day4
{
private:
	std::string _filename;
public: 
	Day4(std::string filename);
	int FirstPuzzle();
	int LastPuzzle();
};

