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
#include "SubjectInterface.h"
#include "ObserverInterface.h"

using namespace std;
class StrategyPlayerInterface;
class GameMap;
	
class Player : public SubjectInterface
{
private:
	vector<EffectCard> cards;
	vector<Token> tokens;
	Monster monster;
	Region& region;
	Dices dices;
	int energyCubes;
	string turnPhase;
	string name;
	bool superStar=false;
	StrategyPlayerInterface* playerBehaviour;
	vector<ObserverInterface*> observers;
	vector<string> resolved; // Is used for the observer to know in which order we resolved dices once we notify it.
	bool wasMoved; // For observer to know if player moved or not.

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

	string getTurnPhase();
	vector<string> getResolved();
	bool getMovedStatus();
	StrategyPlayerInterface* getPlayerBehaviour();

	void move(Player & player, GameMap & gameMap, bool gotAttacked) ;
	void resolveDices(Player & player, GameMap& gameMap, vector<Player*> & players);
	void diceRoll(Player & player, bool extraDices);
	void buyCards(Player & player, vector<EffectCard>& buyableCards, EffectCardDeck & effectCards);

	//Mathods of the observer
	virtual void registerOb(ObserverInterface* ob) ;
	virtual void removeOb(ObserverInterface* ob);
	virtual void notifyOb();

	friend ostream & operator<<(ostream & os, const Player & player);
};

