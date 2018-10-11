#pragma once

#include "GraphGeneric.h"
#include "Region.h"

using namespace std;


class GameMap
{
private: 
	GraphGeneric<Region> connectRegions;
	vector<Region> allRegions;
public:
	GameMap();
	GameMap(GraphGeneric<Region> connectRegion);
	~GameMap();
	GraphGeneric<Region> getMapGraph();
	vector<Region> getAllRegions();
	bool setOwnerRegion(string name,Region region);
	vector<string> getOwners(Region region);
	friend ostream& operator<<(ostream & os, GameMap & gameMap);
};

