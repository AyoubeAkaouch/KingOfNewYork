#include "EffectCardDeck.h"
#include <algorithm>

using namespace std;

EffectCardDeck::EffectCardDeck(vector<EffectCard*> cards)
{
	deckOfCards = cards;
}

EffectCardDeck::EffectCardDeck()
{
}

EffectCardDeck::~EffectCardDeck()
{
	//Deleting cards still in deck
	for (auto * card : deckOfCards) {
		delete card;
		card = NULL;
	}
	//Deleting cards that have been used
	for (auto * card : notInDeckCards) {
		delete card;
		card = NULL;
	}
}

void EffectCardDeck::shuffle()
{
	random_shuffle(deckOfCards.begin(), deckOfCards.end());
}

void EffectCardDeck::setDeck(vector<EffectCard*> cards)
{
	this->deckOfCards = cards;
}

EffectCard* EffectCardDeck::draw()
{
	EffectCard* card = deckOfCards[deckOfCards.size() - 1];
	notInDeckCards.push_back(card);//Adding this card to keep track, have to delete it later

	deckOfCards.erase(deckOfCards.end()-1);
	return card;
}

vector<EffectCard*> EffectCardDeck::getAllCards() 
{
	return deckOfCards;
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

