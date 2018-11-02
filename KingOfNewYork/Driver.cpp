#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>
#include "LoadGamePieces.h"
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
	
	//Setup the number of players and associate them to a monster card
	int numberOfPlayers;
	do {
		cout << "How many players will be playing this game? (Has to be between 2 or 6 players)" << endl;
		cin >> numberOfPlayers;
	} while (numberOfPlayers < 2 || numberOfPlayers > 6);

	vector<Player> players;// Have to keep track of the order of for them to play in the right order

	cout << "Please select your player in the clockwise order you are sitting." << endl;
	for (int i = 1; i <= numberOfPlayers; i++) {
		int x;
		cout << "Player " << i << " please choose from this list which monster you want to pick.(Choose by index)" << endl;
		cout << "{ ";
		for (int j = 0; j < monsters.size();j++) {
			cout <<"\""<< monsters[j].getName()<<"\" ";
		}
		cout << " }" << endl;
		cin >> x;
		players.push_back(Player(monsters[x]));
		monsters.erase(monsters.begin()+x);
	}

	cout << "Here are the size of the decks created." << endl;
	cout << "Deck of building tiles: " << tilesDeck.sizeOfDeck() << endl;
	cout << "Deck of cards: " << cardDeck.sizeOfDeck() << endl;
	cout << "Number of Web tokens: " << tokens["Web"].size() << endl;
	cout << "Number of Jynx tokens: " << tokens["Jynx"].size() << endl;
	cout << "Number of Souvenir tokens: " << tokens["Souvenir"].size() << endl;
	cout << "Number of Carapace tokens: " << tokens["Carapace"].size() << endl;


	///////////////////////////////////PART 2 here///////////////////////////////////////

	//Determining order of the turns
	int currentPlayersTurn = firstPlayer(players); //Gives the index in the vector of which player plays first

	//Putting players in regions
	setting
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

