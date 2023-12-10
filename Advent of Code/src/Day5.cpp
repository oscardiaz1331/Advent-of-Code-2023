#include "Day5.h"

Day5::Day5(std::string filename) :_filename(filename)
{
	ReadInfo();
}

int Day5::FirstPuzzle()
{
	int result = 0;
	for (auto& seed : seeds) 
	{
		for (auto transformationMap : transformations) 
		{
			for (auto section : transformationMap)
			{
				if (seed >= std::get<0>(section) && seed < std::get<1>(section)) 
				{
					seed += std::get<2>(section);
					break;
				}
			}
		}
	}
	result=*std::min_element(seeds.begin(), seeds.end());
	return result;
}

int Day5::LastPuzzle()
{
	return 0;
}

void Day5::ReadInfo()
{
	std::ifstream ifs(_filename);
	std::string line, mapInfo;
	std::getline(ifs, line);
	std::istringstream lineStream(line);
	lineStream >> mapInfo;
	double num, destination, source, length;
	while (!lineStream.eof())
	{
		lineStream >> num;
		seeds.push_back(num);
	}
	int nMaps = 0;
	while (!ifs.eof())
	{
		std::getline(ifs, line);
		if (!line.empty())
		{
			lineStream = std::istringstream(line);
			int pos = line.find("map");
			if (pos != -1)
			{
				std::getline(lineStream,line);
				transformations.push_back({});
				nMaps++;
			}
			else
			{
					lineStream >> destination >> source >> length;
					std::tuple<double, double, double> trans({source, source + length, -source + destination});
					transformations[nMaps - 1].push_back(trans);
			}
		}
	}
}