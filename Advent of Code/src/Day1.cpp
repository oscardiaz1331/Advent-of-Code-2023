#include "Day1.h"

Day1::Day1(std::string filename) : _filename(filename)
{
}

int Day1::FirstPuzzle()
{
	std::ifstream ifs(_filename);
	int result = 0;
	for (std::string line; std::getline(ifs, line); )
	{
		bool firstDigitFound = false;
		int firstDigit, lastDigit;
		for (auto it = line.begin(); it != line.end(); it++)
		{
			if (std::isdigit(*it))
			{

				const char digit = *it;
				if (!firstDigitFound)
				{
					firstDigit = std::atoi(&digit);
					firstDigitFound = true;
				}
				lastDigit = std::atoi(&digit);
			}
		}
		if (firstDigitFound) {
			result += firstDigit * 10 + lastDigit;
		}
	}
	return result;
}

int Day1::SecondPuzzle()
{
	std::ifstream ifs(_filename);
	int result = 0;
	for (std::string line; std::getline(ifs, line); )
	{
		int firstDigit = 0, lastDigit = 0, stringSize = line.size();
		if (stringSize != 0) {
			int auxFirstPos = stringSize, auxLastPos = 0;
			for (auto& pair : _wordToNumber)
			{
				std::string tempString = line;
				int pos = 0;
				while (pos != -1) {
					pos = tempString.find(pair.first);
					if (pos >= 0)
					{
						tempString.replace(pos, 1, "?");
						if (pos < auxFirstPos)
						{
							auxFirstPos = pos;
							firstDigit = pair.second;
						}
						if (pos >= auxLastPos)
						{
							auxLastPos = pos;
							lastDigit = pair.second;
						}
					}
				}
			}
			result += firstDigit * 10 + lastDigit;
		}
	}
	return result;
}

