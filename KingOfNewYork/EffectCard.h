#pragma once
#include <string>
#include <map>
#include <vector>
#include "SubjectInterface.h"
#include "ObserverInterface.h"

using namespace std;
class EffectCard : public SubjectInterface
{
	string name;
	string type;
	int cost;
	string howToPlay;
	map<string, int> effects; //Key: Category affecting Value: What it is affecting
	vector<ObserverInterface*> observers;
public:
	EffectCard(int cost, string type, string name, string howToPlay, map<string, int> effects);
	EffectCard();
	~EffectCard();
	string getName() const;
	int getCost() const;
	string getDescription() const;
	map<string, int>* getEffects();
	void useCard();

	//Methods of the observer
	virtual void registerOb(ObserverInterface* ob);
	virtual void removeOb(ObserverInterface* ob);
	virtual void notifyOb();

	friend ostream & operator<<(ostream & os, const EffectCard & card);
};

