#include "EffectCardDeck.h"
#include <algorithm>

using namespace std;

EffectCardDeck::EffectCardDeck(vector<EffectCard> cards)
{
	deckOfCards = cards;
}

EffectCardDeck::~EffectCardDeck()
{
}

void EffectCardDeck::shuffle()
{
	random_shuffle(deckOfCards.begin(), deckOfCards.end());
}

EffectCard EffectCardDeck::draw()
{
	EffectCard card = deckOfCards[deckOfCards.size() - 1];
	deckOfCards.erase(deckOfCards.end()-1);
	return card;
}

vector<EffectCard> EffectCardDeck::getAllCards() 
{
	return deckOfCards;
}

//Used to pick a single card
EffectCard EffectCardDeck::pickCard(string name) 
{
	for (int i = 0; i < deckOfCards.size(); i++)
	{
		if (deckOfCards[i].getName() == name)
		{
			EffectCard card = deckOfCards[i];
			deckOfCards.erase(deckOfCards.begin() + i);
			return card;
		}
	}

	//If that token/monster does not exist it will return a card with an empty name!!! Check if valid when called (Implement exception later)
	return EffectCard();
}

int EffectCardDeck::sizeOfDeck() const
{
	return deckOfCards.size();
}

ostream & operator<<(ostream & os, const EffectCardDeck & deck)
{
	os << "Here are all cards inside this deck:\n";

	for (int i = deck.sizeOfDeck()-1; i >= 0; i--)
	{
		os << deck.deckOfCards[i]<<endl;
		//os << "{Card Name: " << deck.deckOfCards[i]->getName() << endl;
		//os << "Description: \"" << (deck.deckOfCards[i])->getDescription() << "\"}" << endl;
	}

	return os;
}

