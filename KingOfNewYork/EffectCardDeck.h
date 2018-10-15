#pragma once
#include "EffectCard.h"
#include <vector>

using namespace std;

class EffectCardDeck
{
private:
	vector<EffectCard> deckOfCards;
public:
	EffectCardDeck(vector<EffectCard> cards);
	~EffectCardDeck();
	void shuffle();
	EffectCard draw();
	vector<EffectCard> getAllCards();
	EffectCard  pickCard(string name);
	int sizeOfDeck() const;
	friend ostream & operator<<(ostream & os, const EffectCardDeck & deck);
};

