#include<vector>
#include<iostream>
#include<string>
#include <cstdlib>
#include <ctime>
#include <map>
#include "GraphGeneric.h"
#include "SubRegion.h"
#include "Region.h"
#include "GameMap.h"
#include "MapLoader.h"
#include "Dices.h"
#include "EffectCardDeck.h"
#include "EffectCard.h"
#include "BuildingTiles.h"
#include "BuildingTilesDeck.h"
#include "Monster.h"
#include "Player.h"
using namespace std;



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

	//Display the roll history
	dices.showRollHistory();

	cout << "--------------------------------PART 5--------------------------------" << endl;
	//Creating cards
	std::map<string, int> effectPlaceholder;
	vector<EffectCard> cardObjects;
	effectPlaceholder["victory"] = 2;

	for (int i= 0; i < 10; i++)
	{
		string cardName = "Card" + to_string(i);
		cardObjects.push_back((EffectCard(i,cardName, "PlaceHolder definition for the moment", effectPlaceholder)));
	}
	
	//Creating a deck object from the cards

	EffectCardDeck cardDeck = EffectCardDeck(cardObjects);
	cout << cardDeck;

	//Shuffling the cards
	cardDeck.shuffle();
	cout << "\nHere are the cards after the shuffle:\n"<<cardDeck;


	//Drawing the top card
	EffectCard pickedCard = cardDeck.draw();

	cout << "The drawn card is: \n" << pickedCard << "\nAnd the rest of the cards in the deck are:\n"<<cardDeck;


	//Creating building tiles
	vector<BuildingTiles> buildingTiles;
	buildingTiles.push_back(BuildingTiles("Building1"));
	buildingTiles.push_back(BuildingTiles("Building2"));
	buildingTiles.push_back(BuildingTiles("Building3"));
	buildingTiles.push_back(BuildingTiles("Hospital2"));
	buildingTiles.push_back(BuildingTiles("Hospital3"));
	buildingTiles.push_back(BuildingTiles("Plant2"));
	buildingTiles.push_back(BuildingTiles("Plant3"));
	BuildingTilesDeck tilesDeck = BuildingTilesDeck(buildingTiles);

	cout << "\n\nHere is the building tiles deck content!\n" << tilesDeck;
	//Shuffling tiles
	cout << "Shuffling the tiles deck!!\n\n";
	tilesDeck.shuffle();
	cout << tilesDeck;

	//Picking top tile
	cout << "\nPicking the top tile:" << tilesDeck.draw();


	//Creating a monster and showing its info
	Monster monster = Monster("Detective");
	cout << "\nCreated monster here is its info!" << monster;

	cout << "--------------------------------PART 4--------------------------------" << endl;
	Player player = Player(monster,&queens);
	cout << "\nCreated a new player and placed it in Queens.\n Will now show the first dice roll\n";
	//Rolling dices
	player.RollDices();
	cout << *player.getDices() << endl;
	//Resolve dices
	//player.resolveDices();
	//Make the player move.
	cout << "\nMoving the player from Queens to Brooklyn\n";
	player.move(&map, &brooklyn);

	//Displaying current owner of brooklyn now
	cout << "\nDisplaying owners for Queens and Brooklyn to see if change move was made properly\n";
	queens.displayOwners();
	brooklyn.displayOwners();

	//Showing how many cards the user owns.
	player.displayCards();

	//Giving player energy cubes to test buying cards
	cout << "\nPlayer was given 4 energy cubes, he will now try to buy Card4 worth 4 energy.\n";
	player.addEnergyCubes(4);
	player.buyCards(cardObjects[4],&cardDeck);

	//Showing how many cards the player now owns.
	player.displayCards();
	cout <<"\nCard4 is now removed from the deck!" <<cardDeck << endl;

	//Trying to buy a card now that the user does not have any funds
	cout << "Trying to buy a card now that the user does not have any funds for and a card not currently in the deck\n";
	player.buyCards(cardObjects[2], &cardDeck);
	player.addEnergyCubes(20);
	player.buyCards(cardObjects[4], &cardDeck);


}

