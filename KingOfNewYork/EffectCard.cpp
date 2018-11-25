#include "EffectCard.h"
#include <iostream>

EffectCard::EffectCard(int cost, string type, string name, string howToPlay, map<string, int> effects)
{
	this->cost = cost;
	this->name = name;
	this->type = type;
	this->howToPlay = howToPlay;
	this->effects = effects;
}

EffectCard::EffectCard()
{
	name = "";
}

EffectCard::~EffectCard()
{
	//Deleting observer in driver since we use 1 observer for all effectcards!
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

void EffectCard::useCard()
{
	this->notifyOb();
}

void EffectCard::registerOb(ObserverInterface * ob)
{
	this->observers.push_back(ob);
}

void EffectCard::removeOb(ObserverInterface * ob)
{
	for (int i = 0; i < observers.size(); i++) {
		if (observers[i] == ob) {
			observers.erase(observers.begin() + i);
			break;
		}
	}
}

void EffectCard::notifyOb()
{
	for (int i = 0; i < observers.size(); i++) {
		observers[i]->update(this); //Passing the player to make the observer aware of which player got updated. 
	}
}

ostream & operator<<(ostream & os, const EffectCard & card)
{
	os << "{Card Name: " << card.getName();
	os << " || Card price: " << card.getCost();
	os << " || Description: \"" << card.getDescription() << "\"}"<<endl;
	return os;
}
