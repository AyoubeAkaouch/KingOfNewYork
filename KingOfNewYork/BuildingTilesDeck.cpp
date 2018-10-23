#include "BuildingTilesDeck.h"
#include <algorithm>
#include <iostream>

using namespace std;

BuildingTilesDeck::BuildingTilesDeck(vector<BuildingTiles> cards)
{
	deckOfCards = cards;
}

BuildingTilesDeck::BuildingTilesDeck()
{
}

BuildingTilesDeck::~BuildingTilesDeck()
{
}

void BuildingTilesDeck::shuffle()
{
	random_shuffle(deckOfCards.begin(), deckOfCards.end());
}

void BuildingTilesDeck::setDeck(vector<BuildingTiles> deck)
{ 
	this->deckOfCards = deck;
}

BuildingTiles BuildingTilesDeck::draw()
{
	BuildingTiles card = deckOfCards[deckOfCards.size() - 1];
	deckOfCards.erase(deckOfCards.end()-1);
	return card;
}

vector<BuildingTiles> BuildingTilesDeck::getAllCards()
{
	return deckOfCards;
}

//Used to pick a single card
BuildingTiles BuildingTilesDeck::pickCard(string name) //Use this for picking tokens, monsters, etc. TO DRAW A CARD USE draw()
{
	for (int i = 0; i < deckOfCards.size(); i++)
	{
		if (deckOfCards[i].getName() == name)
		{
			BuildingTiles card = deckOfCards[i];
			deckOfCards.erase(deckOfCards.begin() + i);
			return card;
		}
	}

	//If that token/monster does not exist it will return a card with an empty name!!! Check if valid when called (Implement exception later)
	return BuildingTiles();
}

int BuildingTilesDeck::sizeOfDeck() const
{
	return deckOfCards.size();
}

ostream & operator<<(ostream & os, const BuildingTilesDeck & deck)
{
	os << "Here are all cards inside this deck:\n";
	for (int i = deck.sizeOfDeck() - 1; i >= 0; i--)
	{
		os << deck.deckOfCards[i];
	}

	return os;
}

