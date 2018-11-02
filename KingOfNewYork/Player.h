#pragma once
#include <vector>
#include <string>
#include "EffectCard.h"
#include "Token.h"
#include "Monster.h"
#include "Region.h"
#include "Dices.h"
#include "GameMap.h"
#include "EffectCardDeck.h"

using namespace std;

class Player
{
private:
	vector<EffectCard> cards;
	vector<Token> tokens;
	Monster monster;
	Region* region;
	Dices dices;
	int energyCubes;
	string name;

public:
	Player();
	Player(Monster monster);
	Player(Monster monster, Region* region);
	~Player();

	map<int, string> RollDices(); // For first roll
	map<int, string> RollDicesExtra(); // For first roll
	map<int, string> RollDices(vector<int>* dicesToRoll); //For rerolls
	map<int, string> RollDicesExtra(vector<int>* dicesToRoll); //For rerolls
	Dices&  getDices();	
	void resolveDices();

	void displayCards();
	void move(GameMap& gameMap,Region& region);
	void buyCards(EffectCard card, EffectCardDeck* deck);
	string getName();
	void addEnergyCubes(int i);
	int getHealth() const;
	int getVictoryPoints() const;
	void addHealth(int health);
	void removeHealth(int health);
	void addPoints(int points);
	void removePoints(int points);
	friend ostream & operator<<(ostream & os, const Player & player);
};

