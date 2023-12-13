#include "Day5.h"
#include <iostream>

Day5::Day5(std::string filename) :_filename(filename)
{
	ReadInfo();
	//Sort the sections of the transformations
	for (auto& map : transformations) {
		std::sort(map.begin(), map.end(), [](const std::tuple<double, double, double>& t1, const std::tuple<double, double, double>& t2) {
			return std::get<0>(t1) < std::get<0>(t2);
			});
	}
}

//In the first puzzle, I transform each seed in all map sequently: when I finish this seed in all maps, I pass to the next seed
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
	result = *std::min_element(seeds.begin(), seeds.end());
	return result;
}

//In the last puzzle, I transform all seeds in each map sequently: when I finish this map with all seeds, I pass to the next map
int Day5::LastPuzzle()
{
	int result = 0;
	std::vector<std::vector<double>> seedsSecondVersion;
	for (int i = 0; i < seeds.size(); i += 2)
	{
		seedsSecondVersion.push_back({ seeds[i],seeds[i + 1] + seeds[i] });
	}
	for (auto transformationMap : transformations)
	{
		std::sort(seedsSecondVersion.begin(), seedsSecondVersion.end(), [](const std::vector<double>& v1, const std::vector<double>& v2) {
			return v1[0] < v2[0];
			});
		std::vector<double> newSeed;
		int sectionNumber = 0;
		for (auto it = seedsSecondVersion.begin(); it < seedsSecondVersion.end();)
		{
			newSeed.clear();
			std::vector<double> seed = *it;
			if (sectionNumber >= transformationMap.size())
			{
				it++;
			}
			else {
				std::tuple<double, double, double> section = transformationMap[sectionNumber];
				if (seed[0] > std::get<1>(section))  //seed bigger than section upper limit
				{
					sectionNumber++;
				}
				else if (seed[1] < std::get<0>(section))
				{
					it++;
				}
				else if (seed[0] >= std::get<0>(section) && seed[0] <= std::get<1>(section))
				{
					//FirstPuzzle Case
					if (seed[1] < std::get<1>(section))
					{
						seed[0] += std::get<2>(section);
						seed[1] += std::get<2>(section);
						*it = seed;
						it++;
					}
					else //New scenario, initial seed range inside the map and the last seed rande outside the map
					{
						newSeed.push_back(std::get<1>(section) + 1);
						newSeed.push_back(seed[1]);
						seed[0] += std::get<2>(section);
						seed[1] = std::get<1>(section) + std::get<2>(section);
						*it = seed;
						it = seedsSecondVersion.insert(++it, newSeed);
					}
				}
				else if (seed[0] < std::get<0>(section))
				{
					if (seed[1] >= std::get<0>(section) && seed[1] < std::get<1>(section))
					{
						newSeed.push_back(std::get<0>(section) + std::get<2>(section));
						newSeed.push_back(seed[1] + std::get<2>(section));
						seed[1] = std::get<0>(section) - 1;
						*it = seed;
						it=seedsSecondVersion.insert(++it, newSeed);
						it++;
					}
					else //Case with seed[1] > section[1] because the alternative is checked before
					{
						std::vector<double> auxSeed;
						auxSeed.push_back(std::get<0>(section) + std::get<2>(section));
						auxSeed.push_back(std::get<1>(section) + std::get<2>(section));
						newSeed.push_back(std::get<1>(section) + 1);
						newSeed.push_back(seed[1]);
						seed[1] = std::get<0>(section) - 1;
						*it = seed;
						it=seedsSecondVersion.insert(++it, auxSeed);
						it=seedsSecondVersion.insert(++it, newSeed);
						newSeed.clear();
					}
				}
			}
		}
	}
	std::sort(seedsSecondVersion.begin(), seedsSecondVersion.end(), [](const std::vector<double>& v1, const std::vector<double>& v2) {
		return v1[0] < v2[0];
		});
	result = seedsSecondVersion[0][0];
	return result;
}

void Day5::ReadInfo()
{
	std::ifstream ifs(_filename);
	std::string line, mapInfo;
	std::getline(ifs, line);
	std::istringstream lineStream(line);
	lineStream >> mapInfo;
	double num, num2, destination, source, length;
	while (!lineStream.eof())
	{
		lineStream >> num >> num2;
		seeds.push_back(num);
		seeds.push_back(num2);
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
				std::getline(lineStream, line);
				transformations.push_back({});
				nMaps++;
			}
			else
			{
				lineStream >> destination >> source >> length;
				std::tuple<double, double, double> trans({ source, source + length-1, -source + destination });
				transformations[nMaps - 1].push_back(trans);
			}
		}
	}
}