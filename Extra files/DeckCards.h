#pragma once
#include "Card.h"
#include <vector>

using namespace std;

class DeckCards
{
private:
	vector<Card*> deckOfCards;
public:
	DeckCards(vector<Card*> cards);
	~DeckCards();
	void shuffle();
	Card* draw();
	vector<Card*>* getAllCards();
	Card* pickCard(string name);
	int sizeOfDeck() const;
	friend ostream & operator<<(ostream & os, const DeckCards & deck);
};

