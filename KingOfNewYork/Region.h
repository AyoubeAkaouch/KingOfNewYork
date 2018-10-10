#ifndef REGION_H
#define REGION_H

using namespace std;

#include "SubRegion.h"
#include "GraphGeneric.h"



class Region
{
public:
	Region();
	Region(GraphGeneric<SubRegion> subRegion);
	Region(int maxPlayers);//Creates a region with no subregions.
	~Region();
	const Region* pointer = this;
	vector<string> getOwners();// Change for player object
	bool setOwner(string player);// Take player object after
	void removePlayer(string player);// Take player object after
	void addSubRegion(GraphGeneric<SubRegion> subRegionGraph); //Check if there is an owner and add it to current owners
	bool operator ==(const Region& object2) const;
private:
	//Change this to vector of subregion instead of strings??
	vector<GraphGeneric<SubRegion>> subRegions; //Subregion can be empty if it does not have any subregion.
	vector<string> currentOwners;// Change for player object after
	string findOwnerOfSubregions(GraphGeneric<SubRegion> graph);
	int maxPlayers;
};

#endif
// Have a hashmap of which subregion is owned by which player???