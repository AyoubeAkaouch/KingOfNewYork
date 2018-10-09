#include "SubRegion.h"
#include "Region.h"
#include <iostream>
using namespace std;



SubRegion::SubRegion(GraphGeneric<SubRegion> inGraph)
{
	this->inGraph = inGraph;
	this->owner = "";
}



SubRegion::~SubRegion()
{
}

bool SubRegion::findOwnerOfSubregions()
{
	bool exists = false;
	vector<SubRegion> allNodes = inGraph.getAllNodes();

	for (size_t i = 0; i < allNodes.size(); i++) {
		if (allNodes[i].getOwner() != "") {
			exists = true;
		}
	}
	return exists;
}

bool SubRegion::setOwner(string owner) //When moving a player in the same subregion no need to use this and check, bc already setup and we know we are the owner. 
{
	if (findOwnerOfSubregions())
	{
		cout << "Can't set this player as the owner of this subregion, someone already owns this subregion." << endl;
		return false;
	}
	else 
	{
		this->owner = owner;
		cout << owner << " was set as owner of this subregion" << endl;
		return true;
	}
	

}

string SubRegion::getOwner()
{
	return owner;
}

