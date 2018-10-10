#include <iostream>
using namespace std;
#include "SubRegion.h"



SubRegion::SubRegion(string name, GraphGeneric<SubRegion>* inGraph)
{
	this->name = name;
	this->inGraph = inGraph;
	this->owner = "";
}



SubRegion::~SubRegion()
{
}

bool SubRegion::findOwnerOfSubregions()
{
	bool exists = false;
	vector<SubRegion> allNodes = inGraph->getAllNodes();

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

bool SubRegion::operator==(const SubRegion & object2) const
{
	if (object2.pointer == this->pointer)
		return true;
	else
		return false;
}


ostream & operator<<(ostream & os, const SubRegion & subRegion)
{

	os <<"\""<< subRegion.name<< "\"" ;
	return os;
}
