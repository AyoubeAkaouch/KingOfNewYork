#pragma once
#include <string>
#include "Region.h"
#include "GraphGeneric.h"

using namespace std;

class SubRegion
{
public:
	SubRegion(GraphGeneric<SubRegion> inGraph);
	~SubRegion();
	bool findOwnerOfSubregions();
	bool setOwner(string owner);//Change this to player when implemented
	string getOwner();// In region class, findOwnerOfSubRegions was coded under the assumption if no owner we return ""
private:
	string owner; //Change this to player when implemented
	Region partOf; //Might not need it just for future purposes
	GraphGeneric<SubRegion> inGraph;// In which graph this subGraph is a part of (for moves and owner info in the future)
};


