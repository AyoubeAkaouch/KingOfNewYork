#include "DeckCards.h"
#include <algorithm>

using namespace std;

DeckCards::DeckCards(vector<Card*> cards)
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

Card* DeckCards::draw()
{
	Card* card = deckOfCards[deckOfCards.size()-1];
	deckOfCards.erase(deckOfCards.end());
	return card;
}

vector<Card*>* DeckCards::getAllCards() 
{
	return &deckOfCards ;
}

Card* DeckCards::pickCard(string name) //Use this for picking tokens, monsters, etc. TO DRAW A CARD USE draw()
{
	for (int i = 0;i<deckOfCards.size();i++)
	{
		if (deckOfCards[i]->getName() == name)
		{
			Card* card = deckOfCards[i];
			deckOfCards.erase(deckOfCards.begin()+i);
			return card;
		}
	}

	//If that token/monster does not exist it will return a card with an empty name!!! Check if valid when called (Implement exception later)
	return nullptr;
}

int DeckCards::sizeOfDeck() const
{
	return deckOfCards.size();
}

ostream & operator<<(ostream & os, const DeckCards & deck)
{
	os << "Here are all cards inside this deck:\n";
	for (int i = deck.sizeOfDeck()-1;i>=0;i--)
	{
		os << (deck.deckOfCards[i])->getName();
	}

	return os;
}

