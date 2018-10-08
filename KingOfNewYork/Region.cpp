#include "Region.h"



Region::Region()
{
}

Region::Region(GraphGeneric<SubRegion> subRegion)
{
	subRegions.push_back(subRegion);
}


Region::~Region()
{
}

vector<string> Region::getOwners()
{
	if (currentOwners.size == 0) {
		cout << "There are no players currently in this region. Vector is empty." << endl;
	}
	
	return currentOwners;
}

void Region::setOwner(string player)
{
	this->currentOwners.push_back(player);
}

