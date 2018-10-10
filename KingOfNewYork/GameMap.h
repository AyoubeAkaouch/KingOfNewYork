#pragma once

#include "GraphGeneric.h"
#include "Region.h"

using namespace std;


class GameMap
{
private: 
	GraphGeneric<Region> connectRegions;
public:
	GameMap();
	GameMap(GraphGeneric<Region> connectRegion);
	~GameMap();
};

