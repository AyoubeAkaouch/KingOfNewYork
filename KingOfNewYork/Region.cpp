#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "Region.h"


Region::Region()
{
}

Region::Region(string name )
{
	this->name = name;
	maxPlayers = 2;//Default number of players
}

Region::Region(string name,GraphGeneric<SubRegion> subRegion)//Creates a region with 1 subregion
{
	this->name = name;
	string player = findOwnerOfSubregions(subRegion);
	subRegions.push_back(subRegion);
	maxPlayers = 1;
	if (player != "")//If someone is already in this subregion graph add it as a player
		setOwner(player);
}

Region::Region(string name, int maxPlayers)//Creates a region with no subregions
{
	this->name = name;
	this->maxPlayers = maxPlayers;
}


Region::~Region()
{
}

vector<string> Region::getOwners()
{
	if (currentOwners.size() == 0) {
		cout << "There are no players currently in "<< name<<". Vector is empty." << endl;
	}
	
	return currentOwners;
}

string Region::getName() const
{
	return this->name;
}

bool Region::setOwner(string player)
{
	if (currentOwners.size() == maxPlayers)
	{
		cout << "Can't add "<< player <<" to "<<name<<" it is already full (max "<<maxPlayers<<" players)." <<endl;
		return false;
	}
	this->currentOwners.push_back(player);
	return true;
}


void Region::removePlayer(string player)
{
	vector<string>::iterator it = currentOwners.begin();
	bool deleted = false;

	for (size_t i = 0; i < currentOwners.size(); i++) {
		if (currentOwners[i] == player) {
			currentOwners.erase(it);
			deleted = true;
		}

		it++;
	}

	if (deleted)
	{
		cout << player << " has been deleted properly." << endl;
	}
	else 
	{
		cout << player << " has not been deleted, it wasn't currently in this region." << endl;

	}

}

void Region::addSubRegion(GraphGeneric<SubRegion> subRegionGraph)
{
	bool alreadyExists = false;

	for (size_t i = 0; i < subRegions.size(); i++) {
		if (&subRegions[i] == &subRegionGraph) {
			alreadyExists = true;
		}
	}

	if (alreadyExists)
	{
		cout << "These subregions were already in this region and not added again."<<endl;
	}
	else
	{
		subRegions.push_back(subRegionGraph);
		cout << "Subregions were succesfully added to this region"<<endl;
	}

}

vector<GraphGeneric<SubRegion>>* Region::getSubRegions()
{
	return &subRegions;
}

bool Region::operator==(const Region & object2) const
{
	if (object2.getName() == this->name)
		return true;
	else
		return false;
}

string Region::findOwnerOfSubregions(GraphGeneric<SubRegion> graph)
{
	string player;//Might change to player object
	vector<SubRegion> subRegions = graph.getAllNodes();
	bool exists = false;

	for (size_t i = 0; i < subRegions.size(); i++) {
		if (subRegions[i].getOwner() != "") {
			player = subRegions[i].getOwner();
			exists = true;
		}
	}
	if (exists)
		return "";
	else
		return player;
}

ostream & operator<<(ostream & os, const Region & region)
{
	os << region.name;
	return os;
}

//Prints subregions and its neighbors, this is now handled by GameMap.cpp
/*ostream & operator<<(ostream & os, const Region & region)
{
	os << "Region: " << region.name;
	if (region.subRegions.size() == 0)
	{
		os << " *No subregions in this region*" << endl;
	}
	else
	{
		os << endl;
		for (size_t i = 0; i < region.subRegions.size(); i++) {
			os << "{"<<endl<<region.subRegions[i]<<" }"<<endl;
		}
	}
	
	return os;
}*/
