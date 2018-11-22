#pragma once
#include "EffectCard.h"
#include <vector>

using namespace std;

class EffectCardDeck
{
private:
	vector<EffectCard*> deckOfCards;
	vector<EffectCard*> notInDeckCards;// Have to keep track of this to delete all cards in destructor once program stops
public:
	EffectCardDeck(vector<EffectCard*> cards);
	EffectCardDeck();
	~EffectCardDeck();
	void shuffle();
	void setDeck(vector<EffectCard*> cards);
	EffectCard* draw();
	vector<EffectCard*> getAllCards();
	int sizeOfDeck() const;
	friend ostream & operator<<(ostream & os, const EffectCardDeck & deck);
};

