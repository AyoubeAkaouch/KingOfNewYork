#ifndef SUBREGION_H
#define SUBREGION_H

#include <string>
#include "GraphGeneric.h"

using namespace std;



class SubRegion
{
private:
	string owner; //Change this to player when implemented
	GraphGeneric<SubRegion> inGraph;// In which graph this subGraph is a part of (for moves and owner info in the future)
public:
	const SubRegion* pointer = this;
	SubRegion(GraphGeneric<SubRegion> inGraph);
	~SubRegion();
	bool findOwnerOfSubregions();
	bool setOwner(string owner);//Change this to player when implemented
	string getOwner();// In region class, findOwnerOfSubRegions was coded under the assumption if no owner we return ""
	bool operator ==(const SubRegion& object2) const;
};


#endif