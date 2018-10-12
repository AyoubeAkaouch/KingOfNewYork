#pragma once
#include "GameMap.h"
#include "Region.h"
#include "SubRegion.h"
#include "GraphGeneric.h"


class MapLoader
{
private:
	vector<string> parseNeighbors(string regionNeighbors);
	vector<vector<string>> parseSubRegions(string subregions);
public:
	MapLoader();
	~MapLoader();
	void mapToFile(GameMap* map);
	GameMap mapLoader(string file);
};

