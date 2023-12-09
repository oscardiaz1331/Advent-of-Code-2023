#pragma once
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>

class Day3
{
private: 
	std::string _filename;
	//std::vector<char> _specialChars{'*','%','=','/','#','&','@','$','-','+'};
public: 
	Day3(std::string filename);
	int FirstPuzzle();
};

