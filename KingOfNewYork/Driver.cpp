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
#include "StrategyPlayerInterface.h"
#include "AggressivePlayerStrategy.cpp"
#include "ConcretePlayerObserver.h"
#include "ConcreteGameMapObserver.h"
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

	ConcretePlayerObserver* playerObserver = new ConcretePlayerObserver();
	ConcreteGameMapObserver* gameMapObserver = new ConcreteGameMapObserver();

	cin >> directory;
	GameMap* gameMap;
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
	
	//Adding an observer to our gameMap
	gameMap->registerOb(gameMapObserver);

	//Setting up the decks and game pieces object
	vector<Monster> monsters;
	BuildingTilesDeck tilesDeck;
	EffectCardDeck cardDeck;
	map<string, vector<Token>> tokens;

	
	
	LoadGamePieces::LoadAllPieces(monsters,tilesDeck, cardDeck,tokens); //This will create all the card objects and their values
	AggressivePlayerStrategy aggressive;
	vector<Player*> players;// Have to keep track of the order of for them to play in the right order
	
	setPlayers(players,monsters,&aggressive,playerObserver);// Method to create the player objects and associate them to monster cards!.

	//Once we create the players we pass them to the GameMap.
	gameMap->addPlayers(&players);


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
	settingRegions(*gameMap,players,firstToPlay);

	//Display the playing order
	cout << "Here is the order in which players are going to play in:" << endl;
	for (int i = 0; i < players.size(); i++) {
		cout << i << ") " << &players[(i + firstToPlay) % players.size()];
	}
	cout << endl;

	gameLoop(players, *gameMap,  cardDeck,  tilesDeck,  tokens, firstToPlay);


	cout << "___________________Final Board___________________" << endl;
	gameMapObserver->update(gameMap);

	cout << "~~~~Here is the info for all players~~~~" << endl;
	for (int i = 0; i < players.size(); i++) {
		cout << "-----------------------------" << endl;
		cout << *players[i] << " ";
		players[i]->displayCards();
		cout << "-----------------------------" << endl;
	}

	//Deleting the Player pointers that we created in the heap
	for (int i = 0; i < players.size(); i++) {
		
		//When deleting the players we will also delete all the design pattern pointers we used!
		delete players[i];
		players[i] = NULL; // To avoid danling pointiers
	}

	//Deleting the Game Map pointer that we got from the maploader!
	delete gameMap;
	gameMap = NULL;//To avoid dangling pointers

	//Deleting the PlayerObserver and GameMap pointer
	delete playerObserver;
	playerObserver = NULL;
	delete gameMapObserver;
	gameMapObserver = NULL;

}

