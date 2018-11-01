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
	string Name;

public:
	Player();
	Player(Monster monster);
	Player(Monster monster, Region* region);
	~Player();
	void RollDices(); // For first roll

	Dices&  getDices();
	void displayCards();
	void RollDices(vector<int>* dicesToRoll); //For rerolls
	void resolveDices();
	void move(GameMap& gameMap,Region& region);
	void buyCards(EffectCard card, EffectCardDeck* deck);
	void addEnergyCubes(int i);
	int getHealth() const;
	int getVictoryPoints() const;
	void addHealth(int health);
	void removeHealth(int health);
	void addPoints(int points);
	void removePoints(int points);
	friend ostream & operator<<(ostream & os, const Player & player);
};

