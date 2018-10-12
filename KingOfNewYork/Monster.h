#pragma once
#include "Card.h"
#include <string>

using namespace std;

class Monster :
	public Card
{
private:
	int hp; //Health Points
	int vp; //Victory Points
	string name;
public:
	Monster(string name);
	~Monster();
	string getName() const;
	int getHealth() const;
	int getVictoryPoints() const;
	void addHealth(int health);
	void removeHealth(int health);
	void addPoints(int points);
	void removePoints(int points);
};

