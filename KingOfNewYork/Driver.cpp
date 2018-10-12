#include<vector>
#include<iostream>
#include<string>
using namespace std;
#include "GraphGeneric.h"
#include "SubRegion.h"
#include "Region.h"
#include "GameMap.h"
#include "MapLoader.h"

int main() {

	
	cout << "--------------------------------PART 1--------------------------------" << endl;
	//Create the map of King Of New York
	GraphGeneric<SubRegion> manhattanSubRegions;
	GraphGeneric<Region> newYork;
	SubRegion lowerManhattan = SubRegion("Lower Manhattan",&manhattanSubRegions);
	SubRegion midtownManhattan = SubRegion("Midtown Manhattan", &manhattanSubRegions);
	SubRegion upperManhattan = SubRegion("Upper Manhattan", &manhattanSubRegions);

	manhattanSubRegions.addEdge(lowerManhattan,midtownManhattan);
	manhattanSubRegions.addEdge(midtownManhattan,upperManhattan);

	Region manhattan = Region("Manhattan", manhattanSubRegions);
	Region bronx = Region("Bronx");
	Region brooklyn = Region("Brooklyn");
	Region queens = Region("Queens");
	Region statenIsland = Region("Staten Island");

	newYork.addEdge(manhattan, bronx);
	newYork.addEdge(manhattan, brooklyn);
	newYork.addEdge(manhattan, queens);
	newYork.addEdge(manhattan, statenIsland);
	newYork.addEdge(bronx, manhattan);
	newYork.addEdge(bronx, brooklyn);
	newYork.addEdge(bronx, queens);
	newYork.addEdge(bronx, statenIsland);
	newYork.addEdge(brooklyn, bronx);
	newYork.addEdge(brooklyn, manhattan);
	newYork.addEdge(brooklyn, queens);
	newYork.addEdge(brooklyn, statenIsland);
	newYork.addEdge(queens, bronx);
	newYork.addEdge(queens, brooklyn);
	newYork.addEdge(queens, manhattan);
	newYork.addEdge(queens, statenIsland);


	GameMap map = GameMap(newYork,"KingOfNewYork");

	cout << "~~~~~~~~~~~~~~~~~~~~~Created map~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << map;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl<<endl;

	cout << "Adding 3 players to Brooklyn (Only 2 spaces available) in this order: Maxime, Lisa, ExcessKid \n{" << endl;
	map.setOwnerRegion("Maxime",brooklyn);
	map.setOwnerRegion("Lisa", brooklyn);
	//Adding an extra player exceeding Brooklyn's capacity
	map.setOwnerRegion("ExcessKid", brooklyn);
	cout << "}\n\nAdding 2 players to Manhattan (Only 1 space available) in this order: Antoine, Joe \n{" << endl;
	//Manhattan only has one spot since we only added 1 subregion graph
	map.setOwnerRegion("Antoine", manhattan);
	map.setOwnerRegion("Joe",manhattan);

	vector<string> ownersManhattan = map.getOwners(manhattan);
	vector<string> ownersBrooklyn = map.getOwners(brooklyn);
	cout << "Players in brooklyn: " << ownersBrooklyn[0] << ", " << ownersBrooklyn[1] << ".\n}";

	
	//An invalid map can't be created because of the checks made during all the gamesetup.
	cout << "\n\n--------------------------------PART 2--------------------------------" << endl;
	cout << "Loading the map\n";
	MapLoader mapLoader = MapLoader();
	GameMap importedMap = mapLoader.mapLoader("..\\\\KingOfNewYork.map");
	cout << endl << endl;

	cout <<"~~~~~~~~~~~~~~~~~~~~~Imported Map~~~~~~~~~~~~~~~~~~~~~\n" <<importedMap;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}