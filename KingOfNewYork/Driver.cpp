#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>
#include "LoadGamePieces.h"
#include "Region.h"
#include "GameMap.h"
#include "MapLoader.h"
#include "EffectCardDeck.h"
#include "BuildingTilesDeck.h"
#include "Monster.h"
#include "Player.h"
#include "DriverMethods.h"
using namespace std;



void getAllMapFiles (string directory){
	cout << "These are all the map files curently in the directory." << endl;
	char commandCd[70];
	string dir = "cd " + directory + " && dir *.map";
	strcpy_s(commandCd, dir.c_str());
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	system(commandCd);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

int main() {
	srand((int)time(0)); // Setting up the seed here, to have random numbers for all dice objects

	string directory, mapFile, completeDirectory;
	cout << "In which dirctory you wish to get your maps from?(If want to use default King Of NewYork map press x)" << endl;
	cin >> directory;
	GameMap gameMap;
	if (directory != "x")
	{
		::getAllMapFiles(directory);
		cout << "\nPlease enter the name of the map file you wish to use: " << endl;
		cin >> mapFile;
		completeDirectory = directory + "\\" + mapFile;
		gameMap = MapLoader::mapLoader(completeDirectory);
	}
	else {
		gameMap = MapLoader::mapLoader("..\\Maps\\KingOfNewYork.map");
	}
	
	//Setting up the decks and game pieces object
	vector<Monster> monsters;
	BuildingTilesDeck tilesDeck;
	EffectCardDeck cardDeck;
	map<string, vector<Token>> tokens;
	
	LoadGamePieces::LoadAllPieces(monsters,tilesDeck, cardDeck,tokens); //This will create all the card objects and their values
	
	vector<Player> players;// Have to keep track of the order of for them to play in the right order
	setPlayers(players,monsters);// Method to create the player objects and associate them to monster cards!.


	cout << "Here are the size of the decks created." << endl;
	cout << "Deck of building tiles: " << tilesDeck.sizeOfDeck() << endl;
	cout << "Deck of cards: " << cardDeck.sizeOfDeck() << endl;
	cout << "Number of Web tokens: " << tokens["Web"].size() << endl;
	cout << "Number of Jynx tokens: " << tokens["Jynx"].size() << endl;
	cout << "Number of Souvenir tokens: " << tokens["Souvenir"].size() << endl;
	cout << "Number of Carapace tokens: " << tokens["Carapace"].size() << endl;


	///////////////////////////////////PART 2 here///////////////////////////////////////

	//Determining order of the turns
	cout << endl;
	int firstToPlay = firstPlayer(players); //Gives the index in the vector of which player plays first

	//Putting players in regions
	settingRegions(gameMap,players,firstToPlay);
	vector<Region> regions = gameMap.getAllRegions();

	//Display the playing order
	cout << "Here is the order in which players are going to play in:" << endl;
	for (int i = 0; i < players.size(); i++) {
		cout << i << ") " << players[(i + firstToPlay) % players.size()];
	}
	cout << endl;

	cout << "Here are all the regions and their players:" << endl;
	for (int i = 0; i < regions.size();i++ ) {
		cout << regions[i].getName() << ": ";
		regions[i].displayOwners();
	}

	///////////////////////////////////PART 3 here///////////////////////////////////////

	/*Dices diceTest;
	vector<int> toRoll = {1,2,5,0,7};
	diceTest.firstRollExtra();
	cout << diceTest << endl;	
	diceTest.reroll(&toRoll);
	cout << diceTest << endl;
	toRoll = { 1,2,3,4 };
	diceTest.reroll(&toRoll);
	cout << diceTest << endl;
	diceTest.firstRoll();
	cout << diceTest << endl;
	toRoll = { 1,0,5,6 };
	diceTest.reroll(&toRoll);
	cout << diceTest << endl;

	diceTest.showRollHistory();*/

}

