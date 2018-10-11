#include "GameMap.h"



GameMap::GameMap()
{
}


GameMap::GameMap(GraphGeneric<Region> connectRegion)
{
	this->connectRegions = connectRegion;
	this->allRegions = connectRegion.getAllNodes();
}

GameMap::~GameMap()
{
}

GraphGeneric<Region> GameMap::getMapGraph()
{
	return connectRegions;
}

vector<Region> GameMap::getAllRegions()
{
	return allRegions;
}
bool GameMap::setOwnerRegion(string name,Region region)
{
	for (size_t i = 0; i < allRegions.size(); i++)
	{
		if (allRegions[i] == region)
			return allRegions[i].setOwner(name);
	}
	return false;
}
vector<string> GameMap::getOwners(Region region)
{
	for (size_t i = 0; i < allRegions.size(); i++)
	{
		if (allRegions[i] == region)
			return allRegions[i].getOwners();
	}
	cout << "This region does not exist in this map, returning empty vector"<<endl;
	return vector<string>();
}
ostream & operator<<(ostream & os, GameMap & gameMap)
{
	vector<Region> regions = gameMap.getAllRegions();
	vector<Region> connections;
	vector<GraphGeneric<SubRegion>> subRegionsOfRegion;
	GraphGeneric<SubRegion> subRegionMap;
	GraphGeneric<Region> map = gameMap.getMapGraph();

	for (size_t i = 0; i < regions.size(); i++) {
		os << "Region: "<< regions[i] << endl;
		connections = map.getConnections(gameMap.allRegions[i]);
		subRegionsOfRegion = *regions[i].getSubRegions();
		if (connections.empty())
			os << "{}";
		else
		{
			os << "{";
			for (size_t j = 1; j < connections.size(); j++)//Start at 1 because 0 is the current region
			{
				os << connections[j];
				if (j < connections.size() - 1)
					os << ",";
			}
			os << "}"<< endl;
		}
		if (subRegionsOfRegion.size() == 0)
			os << "{}"<<endl;
		else
		{
			vector<SubRegion> allNodesSubRegion;
			os << "{";
			for (size_t j = 0; j < subRegionsOfRegion.size(); j++)
			{
				os << "{";
				subRegionMap = subRegionsOfRegion[j];
				allNodesSubRegion = subRegionMap.getAllNodes();
				for (size_t k = 0; k < allNodesSubRegion.size(); k++)//Start at 1 because 0 is the current region
				{
					os << allNodesSubRegion[k];
					if (k < allNodesSubRegion.size() - 1)
						os << "->";
				}
				os << "}";
			}
			os << "}"<<endl;
		}



	}

	return os;
}
