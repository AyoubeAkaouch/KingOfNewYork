#include "EffectCard.h"
#include <iostream>

EffectCard::EffectCard(int cost, string name, string howToPlay, map<string, int> effects)
{
	this->cost = cost;
	this->name = name;
	this->howToPlay = howToPlay;
	this->effects = effects;
}

EffectCard::EffectCard()
{
	name = "";
}

EffectCard::~EffectCard()
{
}

string EffectCard::getName() const
{
	return this->name;
}

int EffectCard::getCost() const
{
	return cost;
}

string EffectCard::getDescription() const
{
	return howToPlay;
}

map<string, int>* EffectCard::getEffects()
{
	return &effects;
}

ostream & operator<<(ostream & os, const EffectCard & card)
{
	os << "{Card Name: " << card.getName();
	os << " || Card price: " << card.getCost();
	os << " || Description: \"" << card.getDescription() << "\"}"<<endl;
	return os;
}
