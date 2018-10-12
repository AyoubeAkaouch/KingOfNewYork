#include<vector>
#include<iostream>
#include<string>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "GraphGeneric.h"
#include "SubRegion.h"
#include "Region.h"
#include "GameMap.h"
#include "MapLoader.h"
#include "Dices.h"


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
	cout << "}\n\nPlayers in brooklyn: " << ownersBrooklyn[0] << ", " << ownersBrooklyn[1] << ".\n";
	cout << "Players in Manhattan: " << ownersManhattan[0] ;

	
	//An invalid map can't be created because of the checks made during all the gamesetup.
	cout << "\n\n--------------------------------PART 2--------------------------------" << endl;
	cout << "Loading the map\n";
	MapLoader mapLoader = MapLoader();
	GameMap importedMap = mapLoader.mapLoader("..\\\\KingOfNewYork.map");
	cout << endl << endl;

	cout <<"~~~~~~~~~~~~~~~~~~~~~Imported Map~~~~~~~~~~~~~~~~~~~~~\n" <<importedMap;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;


	cout << "--------------------------------PART 3--------------------------------" << endl;
	srand((int)time(0)); // Setting up the seed here, to have random numbers for all dice objects
	
	vector<int> rolls= { 0,1,2,3,4,5};
	Dices dices;
	char rollAgain;
	bool canRoll = true;
	
	cout << "Dices created!" << endl;
	cout << "\nHere is the first roll :\n"<< dices;
	while (canRoll)
	{
		cout << "Would you like to roll again (y/n)?" << endl;
		cin >> rollAgain;
		if (rollAgain == 'y')
		{
			rolls.clear();
			cout << "Which dices you which to roll again (Input the dice positions with a space in between)?" << endl;
			int reroll;
			string line;
			getline(cin, line);
			getline(cin, line);

			rolls = dices.stringToVectorInt(line);
			
			canRoll = dices.reroll(&rolls);
			cout << "\nHere are your current dices:\n" << dices;
		}
		else
		{
			break;
		}
	}

	cout << "\n\nStarting a second round of rerolls" << endl;
	dices.firstRoll();
	canRoll = true;
	cout << "\nHere is the first roll :\n" << dices;
	while (canRoll)
	{
		cout << "Would you like to roll again (y/n)?" << endl;
		cin >> rollAgain;
		if (rollAgain == 'y')
		{
			rolls.clear();
			cout << "Which dices you which to roll again (Input the dice positions with a space in between)?" << endl;
			int reroll;
			string line;
			getline(cin, line);
			getline(cin, line);

			rolls = dices.stringToVectorInt(line);

			canRoll = dices.reroll(&rolls);
			cout << "\nHere are your current dices:\n" << dices;
		}
		else
		{
			break;
		}
	}

	dices.showRollHistory();
}