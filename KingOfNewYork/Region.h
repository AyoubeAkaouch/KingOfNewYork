#pragma once
#include "SubRegion.h"
#include "GraphGeneric.h"

using namespace std;

class Region
{
public:
	Region();
	Region(GraphGeneric<SubRegion> subRegion);
	Region(int maxPlayers);//Creates a region with no subregions.
	~Region();
	vector<string> getOwners();// Change for player object
	bool setOwner(string player);// Take player object after
	void removePlayer(string player);// Take player object after
	void addSubRegion(GraphGeneric<SubRegion> subRegionGraph); //Check if there is an owner and add it to current owners
private:
	//Change this to vector of subregion instead of strings??
	vector<GraphGeneric<SubRegion>> subRegions; //Subregion can be empty if it does not have any subregion.
	vector<string> currentOwners;// Change for player object after
	string findOwnerOfSubregions(GraphGeneric<SubRegion> graph);

	int maxPlayers;
};


// Have a hashmap of which subregion is owned by which player???