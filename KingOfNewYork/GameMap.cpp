#include "GameMap.h"



GameMap::GameMap()
{
}


GameMap::GameMap(GraphGeneric<Region> connectRegion)
{
	this->connectRegions = connectRegions;
}

GameMap::~GameMap()
{
}
