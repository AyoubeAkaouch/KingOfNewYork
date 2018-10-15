#pragma once
#include "BuildingTiles.h"
#include <vector>

using namespace std;

class BuildingTilesDeck
{
private:
	vector<BuildingTiles> deckOfCards;
public:
	BuildingTilesDeck(vector<BuildingTiles> cards);
	~BuildingTilesDeck();
	void shuffle();
	BuildingTiles draw();
	vector<BuildingTiles> getAllCards();
	BuildingTiles  pickCard(string name);
	int sizeOfDeck() const;
	friend ostream & operator<<(ostream & os, const BuildingTilesDeck& deck);
};

