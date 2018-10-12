#pragma once

#include "GraphGeneric.h"
#include "Region.h"

using namespace std;


class GameMap
{
private: 
	GraphGeneric<Region> connectRegions;
	vector<Region> allRegions;
	string nameOfMap;
public:
	GameMap();
	GameMap(GraphGeneric<Region> connectRegion, string nameOfMap);
	~GameMap();
	GraphGeneric<Region> getMapGraph();
	string getNameMap();
	vector<Region> getAllRegions();
	bool setOwnerRegion(string name,Region region);
	vector<string> getOwners(Region region);
	friend ostream& operator<<(ostream & os, GameMap & gameMap);
};

