#ifndef REGION_H
#define REGION_H

using namespace std;

#include "SubRegion.h"
#include "GraphGeneric.h"



class Region
{
private:
	//Change this to vector of subregion instead of strings??
	vector<GraphGeneric<SubRegion>> subRegions; //Subregion can be empty if it does not have any subregion.
	vector<string> currentOwners;// Change for player object after
	string findOwnerOfSubregions(GraphGeneric<SubRegion> graph);
	int maxPlayers;
	string name;
public:
	Region();
	Region(string name);//Has a default of 2 players
	Region(string name, GraphGeneric<SubRegion> subRegion);
	Region(string name, int maxPlayers);//Creates a region with no subregions.
	~Region();
	const Region* pointer = this; //Testing purposes
	vector<string> getOwners();
	string getName() const;
	// Change for player object
	bool setOwner(string player);// Take player object after
	void removePlayer(string player);// Take player object after
	void addSubRegion(GraphGeneric<SubRegion> subRegionGraph); //Check if there is an owner and add it to current owners
	vector<GraphGeneric<SubRegion>>* getSubRegions();
	bool operator ==(const Region& object2) const;
	void displayOwners();
	friend ostream& operator<<(ostream& os, const Region& region);
};

#endif
// Have a hashmap of which subregion is owned by which player???