#pragma once
#include "GameMap.h"
#include "Region.h"
#include "SubRegion.h"
#include "GraphGeneric.h"


class MapLoader
{
private:
	static vector<string> parseNeighbors(string regionNeighbors);
	static vector<vector<string>> parseSubRegions(string subregions);
public:
	MapLoader();
	~MapLoader();
	static void mapToFile(GameMap* map);
	static GameMap mapLoader(string file);
};

