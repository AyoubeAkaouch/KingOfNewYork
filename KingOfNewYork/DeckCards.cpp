#include "DeckCards.h"
#include <algorithm>

using namespace std;

DeckCards::DeckCards(vector<Card> cards)
{
	deckOfCards = cards;
}

DeckCards::~DeckCards()
{
}

void DeckCards::shuffle()
{
	random_shuffle(deckOfCards.begin(), deckOfCards.end());
}

Card DeckCards::draw()
{
	Card card = deckOfCards[deckOfCards.size()-1];
	deckOfCards.erase(deckOfCards.end());
	return card;
}

vector<Card>* DeckCards::getAllCards()
{
	return &deckOfCards ;
}

Card DeckCards::pickCard(string name) //Use this for picking tokens, monsters, etc. TO DRAW A CARD USE draw()
{
	for (int i = 0;i<deckOfCards.size();i++)
	{
		if (deckOfCards[i].getName() == name)
		{
			Card card = deckOfCards[i];
			deckOfCards.erase(deckOfCards.begin()+i);
			return card;
		}
	}

	
}

int DeckCards::sizeOfDeck()
{
	return deckOfCards.size();
}

