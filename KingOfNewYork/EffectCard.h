#pragma once
#include <string>
#include <map>

using namespace std;
class EffectCard 
{
	string name;
	int cost;
	string howToPlay;
	map<string, int> effects; //Key: Category affecting Value: What it is affecting
public:
	EffectCard(int cost, string name, string howToPlay, map<string, int> effects);
	EffectCard();
	~EffectCard();
	string getName() const;
	int getCost() const;
	string getDescription() const;
	map<string, int>* getEffects();
	friend ostream & operator<<(ostream & os, const EffectCard & card);
};

