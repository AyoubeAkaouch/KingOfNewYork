#include "MapLoader.h"
using namespace std;
#include <iostream>
#include <fstream>
#include <set>
#include <map>


MapLoader::MapLoader()
{
}


MapLoader::~MapLoader()
{
}

vector<string> MapLoader::parseNeighbors(string regionNeighbors)
{
	regionNeighbors = regionNeighbors.substr((regionNeighbors.find("{")+1),(regionNeighbors.find("}") - 1));
	vector<string> parsed;
	int begin = 0;
	for(int i=0;i<regionNeighbors.size();i++)
	{ 
		if (regionNeighbors[i] == ',')
		{
			parsed.push_back(regionNeighbors.substr(begin,(i-begin)));
			begin = i+1;
			
		}
		else if (i == (regionNeighbors.size()-1))
		{
			parsed.push_back(regionNeighbors.substr(begin, i));
		}
	}
	return parsed;
}

vector<vector<string>> MapLoader::parseSubRegions(string subregions)
{
	subregions = subregions.substr(1, subregions.size()-2);
	vector<vector<string>> parsedSubregions;
	int begin = 0;
	for (int i = 0; i < subregions.size(); i++)
	{
		if (subregions[i] == '{') {
			begin = i+1;
			vector<string> subregionConnections;
			for (int j=begin;j<subregions.size();j++)
			{
				if (subregions[j] == '>')
				{
					subregionConnections.push_back(subregions.substr(begin, (j - (begin+1))));
					begin = j + 1;
				}
				else if (subregions[j] == '}')
				{
					subregionConnections.push_back(subregions.substr(begin, (j - begin)));
					begin = j + 1;
					break;
				}
			}
			i = begin - 1;
			parsedSubregions.push_back(subregionConnections);
		}
		
	}
	return parsedSubregions;
}


void MapLoader::mapToFile(GameMap * map)
{
	ofstream output;
	output.open("..\\\\"+map->getNameMap()+".txt");
	output << *map;
	output.close();
}

GameMap* MapLoader::mapLoader(string file)
{
	ifstream input(file);
	//ifstream input2("..\\\\KingOfNewYork.txt");

	string nameOfRegion;
	string regionNeighbors;
	string subregions;
	vector<string> regionNeighborsParsed; // done
	vector<vector<string>> subregionsParsed;//done
	map<string, vector<string>> hashMapRegionInfo;
	map<string, Region> regionsName;
	vector<GraphGeneric<SubRegion>> graphSubRegion;
	GraphGeneric<Region> graphRegion;

	while (!ws(input).eof()) 
	{
		getline(input, nameOfRegion);
		input >> regionNeighbors;
		getline(input, subregions);
		getline(input, subregions);
		nameOfRegion = nameOfRegion.substr(8,nameOfRegion.size());
		//Prints the map
		/*cout << nameOfRegion << endl;
		cout << regionNeighbors<<endl;
		cout << subregions << endl;*/

		vector<string> temp{ regionNeighbors,subregions };
		hashMapRegionInfo[nameOfRegion] = temp;
	}
	input.close();
	map<string, vector<string>>::iterator it;
	
	//Create Regions with their subregion graph (Neighbors are not linked yet)
	for (it = hashMapRegionInfo.begin(); it != hashMapRegionInfo.end(); it++)
	{
		if (it->second[1] != "{}")
		{
			subregionsParsed = parseSubRegions(it->second[1]);
			for (int i = 0; i < subregionsParsed.size(); i++)//Go through all the subregions graph
			{
				graphSubRegion.push_back(GraphGeneric<SubRegion>());
				for (int j = 0; j < subregionsParsed[i].size(); j++)
				{
					graphSubRegion[graphSubRegion.size() - 1].addEdge(SubRegion(subregionsParsed[i][j], &graphSubRegion[graphSubRegion.size() - 1]),
						SubRegion(subregionsParsed[i][j + 1], &graphSubRegion[graphSubRegion.size() - 1]));
					if (j + 2 == subregionsParsed[i].size())
						break;
				}
				
			}
			for (int i = 0; i < subregionsParsed.size(); i++) {
				if (i == 0)
				{	
					regionsName[it->first] = Region(it->first, graphSubRegion[(graphSubRegion.size()-subregionsParsed.size())+i]);
				}
				else {
					regionsName[it->first].addSubRegion(graphSubRegion[(graphSubRegion.size() - subregionsParsed.size()) + i]);
				}
			}
		}
		else
		{
			regionsName[it->first] = Region(it->first);
		}
	}
	//Connecting the neighboring regions together.
	for (it = hashMapRegionInfo.begin(); it != hashMapRegionInfo.end(); it++)
	{
		regionNeighborsParsed = parseNeighbors(it->second[0]);
		for (int i = 0; i < regionNeighborsParsed.size(); i++)
		{

			graphRegion.addEdge(regionsName[it->first],regionsName[regionNeighborsParsed[i]]);
			//cout << "Trying to add this connection: " << regionsName[it->first] << "    " << regionsName[regionNeighborsParsed[i]] << endl;
		}
	}

	return (new GameMap(graphRegion,"ImportedMap"));
}
