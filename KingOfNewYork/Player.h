#pragma once
#include <vector>
#include <string>
#include "EffectCard.h"
#include "Token.h"
#include "Monster.h"
#include "Region.h"
#include "Dices.h"
#include "EffectCardDeck.h"
#include "StrategyPlayerInterface.h"
#include "GameMap.h"

using namespace std;
class StrategyPlayerInterface;
class GameMap;
	
class Player
{
private:
	vector<EffectCard> cards;
	vector<Token> tokens;
	Monster monster;
	Region& region;
	Dices dices;
	int energyCubes;
	string name;
	bool superStar=false;
	StrategyPlayerInterface* playerBehaviour;

public:
	Player();
	Player(Monster monster,StrategyPlayerInterface* playerBehaviour);
	Player(Monster monster, Region& region,StrategyPlayerInterface* playerBehaviour);
	~Player();

	map<int, string> RollDices(); // For first roll
	map<int, string> RollDicesExtra(); // For first roll
	bool RollDices(vector<int>* dicesToRoll); //For rerolls, same method with or without extra dices
	Dices&  getDices();
	map<int, string> getCurrentValues();
	void resolveDices();

	Region& getRegion(); 
	void setRegion(Region& region);

	void displayCards();
	bool buyCards(EffectCard card);
	string getName();
	void addEnergyCubes(int i);
	bool removeEnergy(int i);
	int getEnergyCubes();
	int getHealth() const;
	int getVictoryPoints() const;
	void addHealth(int health);
	void removeHealth(int health);
	void addPoints(int points);
	void removePoints(int points);
	
	bool hasSuperStar();
	void setSuperStar(bool has);

	void move(Player & player, GameMap & gameMap, bool gotAttacked) ;
	void resolveDices(Player & player, GameMap& gameMap, vector<Player*> & players);
	void diceRoll(Player & player, bool extraDices);
	void buyCards(Player & player, vector<EffectCard>& buyableCards, EffectCardDeck & effectCards);

	friend ostream & operator<<(ostream & os, const Player & player);
};

