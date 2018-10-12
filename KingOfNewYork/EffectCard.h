#pragma once
#include "Card.h"
#include <string>
#include <map>

using namespace std;
class EffectCard :
	public Card
{
	string name;
	int cost;
	string howToPlay;
	map<string, int> effects; //Key: Category affecting Value: What it is affecting
public:
	EffectCard(int cost,string howToPlay,map<string, int> effects);
	~EffectCard();
	string getName();
	int getCost();

};

