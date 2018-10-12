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

	newYork.addEdge(manhattan, bronx);
	newYork.addEdge(manhattan, brooklyn);
	newYork.addEdge(manhattan, queens);
	newYork.addEdge(bronx, manhattan);
	newYork.addEdge(bronx, brooklyn);
	newYork.addEdge(bronx, queens);
	newYork.addEdge(brooklyn, bronx);
	newYork.addEdge(brooklyn, manhattan);
	newYork.addEdge(brooklyn, queens);
	newYork.addEdge(queens, bronx);
	newYork.addEdge(queens, brooklyn);
	newYork.addEdge(queens, manhattan);

	GameMap map = GameMap(newYork,"KingOfNewYork");
	//cout << map;
	
	map.setOwnerRegion("Maxime",brooklyn);
	map.setOwnerRegion("Lisa", brooklyn);
	//Adding an extra player exceeding Brooklyn's capacity
	map.setOwnerRegion("Excess Kid", brooklyn);
	//Manhattan only has one spot since we only added 1 subregion graph
	map.setOwnerRegion("Antoine", manhattan);
	map.setOwnerRegion("Joe",manhattan);

	vector<string> ownersManhattan = map.getOwners(manhattan);
	vector<string> ownersBrooklyn = map.getOwners(brooklyn);
	cout << "Players in brooklyn: " << ownersBrooklyn[0] << ", " << ownersBrooklyn[1] << ".";

	
	//An invalid map can't be created because of the checks made during all the gamesetup.


	MapLoader dab = MapLoader();
	//dab.mapToFile(&map);
	cout << endl << endl;
	GameMap importedMap = dab.mapLoader("txtytfr");
	cout <<"------------------IMPORTED---------------------\n" <<importedMap;

}