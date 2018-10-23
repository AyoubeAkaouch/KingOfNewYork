#include<vector>
#include<iostream>
#include<string>
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
		gameMap = MapLoader::mapLoader("C:\\Users\\Ayoube\\source\\repos\\KingOfNewYork\\Maps\\KingOfNewYork.map");
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
		cout << "How many players will be playing this game?" << endl;
		cin >> numberOfPlayers;
	} while (numberOfPlayers < 2 || numberOfPlayers > 6);

	vector<Player> players;// Have to keep track of this order for them to play in the right order

}

