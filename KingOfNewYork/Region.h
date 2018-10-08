#pragma once
#include "SubRegion.h"
#include "GraphGeneric.h"

using namespace std;

class Region
{
public:
	Region();
	Region(GraphGeneric<SubRegion> subRegion);
	~Region();
	vector<string> getOwners();// Change for player object
	void setOwner(string player);// Take player object after
private:
	vector<GraphGeneric<SubRegion>> subRegions;
	vector<string> currentOwners;// Change for player object after

	int maxPlayers;
};