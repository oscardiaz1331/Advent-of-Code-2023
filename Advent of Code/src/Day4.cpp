#include "Day4.h"

Day4::Day4(std::string filename) :_filename(filename)
{
}

int Day4::FirstPuzzle()
{
	std::ifstream ifs(_filename);
	int result = 0;
	std::vector<int> winningNumbers;
	while (!ifs.eof())
	{
		std::string line;
		std::getline(ifs, line);
		std::istringstream lineStream(line);
		std::string lineInfo;
		std::getline(lineStream, lineInfo, ':');//To separate card to winning numbers
		std::getline(lineStream, lineInfo, '|'); //to get winning numbers
		while (lineInfo.back() == ' ')
		{
			lineInfo.pop_back();
		}
		int number;
		std::istringstream numberStream(lineInfo);
		while (!numberStream.eof())
		{
			numberStream >> number;
			winningNumbers.push_back(number);
		}
		std::getline(lineStream, lineInfo);//to get numbers
		int nEquals = -1;
		while (lineInfo.back() == ' ')
		{
			lineInfo.pop_back();
		}
		numberStream = std::istringstream(lineInfo);
		while (!numberStream.eof())
		{
			numberStream >> number;
			for (int winningNumber : winningNumbers)
			{
				if (winningNumber == number)
				{
					nEquals++;
					break;
				}
			}
		}
		if (nEquals > -1) {
			result += pow(2, nEquals);
		}
		winningNumbers.clear();
	}
	return result;
}

int Day4::LastPuzzle()
{
	std::ifstream ifs(_filename);
	int result = 0, nCard = 0, nLines = 0;
	std::string str;
	while (!ifs.eof())
	{
		std::getline(ifs, str);
		nLines++;
	}
	std::vector<int> winningNumbers, numberScratchcards(nLines);
	ifs = std::ifstream(_filename);
	while (!ifs.eof())
	{
		std::string line;
		std::getline(ifs, line);
		std::istringstream lineStream(line);
		std::string lineInfo;
		std::getline(lineStream, lineInfo, ':');//To separate card to winning numbers
		std::istringstream cardStream(lineInfo);
		std::getline(lineStream, lineInfo, '|'); //to get winning numbers
		while (lineInfo.back() == ' ')
		{
			lineInfo.pop_back();
		}
		numberScratchcards[nCard]++;
		int nCopies = numberScratchcards[nCard];
		int number;
		std::istringstream numberStream(lineInfo);
		while (!numberStream.eof())
		{
			numberStream >> number;
			winningNumbers.push_back(number);
		}
		std::getline(lineStream, lineInfo);//to get numbers
		int nEquals = nCard;
		while (lineInfo.back() == ' ')
		{
			lineInfo.pop_back();
		}
		numberStream = std::istringstream(lineInfo);
		while (!numberStream.eof())
		{
			numberStream >> number;
			for (int winningNumber : winningNumbers)
			{
				if (winningNumber == number)
				{
					nEquals++;
					numberScratchcards[nEquals] += nCopies;
					break;
				}
			}
		}
		result += nCopies;
		nCard++;
		winningNumbers.clear();
	}
	return result;
}
