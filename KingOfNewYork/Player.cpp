#include "Player.h"
#include <iostream>

using namespace std;


Player::Player()
{
}

Player::Player(Monster monster)
{
	this->monster = monster;
	this->name = monster.getName();
	this->region = NULL;
	this->energyCubes = 0;
}

Player::Player(Monster monster, Region * region)
{
	this->monster = monster;
	this->region = region;
	this->name = monster.getName();
	region->setOwner(monster.getName());
}

Player::~Player()
{
}

map<int, string> Player::RollDices(vector<int>* dicesToRoll) //For rerolls
{
	dices.reroll(dicesToRoll);
	return dices.getCurrentValues();
}

map<int, string> Player::RollDicesExtra(vector<int>* dicesToRoll)
{
	dices.reroll(dicesToRoll);
	return dices.getCurrentValues();
}

map<int, string> Player::RollDices()
{
	dices.firstRoll();
	return dices.getCurrentValues();
}

map<int, string> Player::RollDicesExtra()
{
	dices.firstRollExtra();
	return dices.getCurrentValues();
}

Dices& Player::getDices()
{
	return dices;
}

string Player::getName() {

	return name;
}
void Player::displayCards()
{
	if (cards.size() == 0)
		cout << this->monster.getName() << " does not own any cards.\n";
	else {
		cout << "Here are the cards owned by " << this->monster.getName() << ": " << endl;
		for (int i = 0; i < cards.size(); i++) {
			cout << "- " << cards[i] << endl;
		}
	}
}

void Player::resolveDices()
{
	string toResolve;
	vector<string> resolved; // Since we are getting a pointer we can't erase from map what has already been resolve, it wil change dice object.
	map<int, string> currentDices = dices.getCurrentValues();
	int dicesResolved = 0;
	while (dicesResolved < 6) //Until all dices are resolved
	{
		cout << "Which effect you want to apply?\n";
		cin >> toResolve;
		for (int i = 0; i < currentDices.size(); i++)
		{
			if (currentDices.at(i) == toResolve && !(find(resolved.begin(), resolved.end(), toResolve) != resolved.end()))
			{
				dices.applyEffect(toResolve);
				dicesResolved++;
			}
		}
		resolved.push_back(toResolve);
	}
}

void Player::move(GameMap& gameMap,Region& region)
{
	//Check if move is possible
	vector<Region> possibleRegions = gameMap.getAllRegions();
	
	if (this->region==NULL)
	{
		this->region = &region;
		cout << "Player succesfully moved!\n";	
	}
	else if (!(find(possibleRegions.begin(), possibleRegions.end(), region) != possibleRegions.end())) // If region doesnt exist
	{
		cout << "This is an illegal move\n";
	}
	else
	{
		this->region->removePlayer(monster.getName());
		region.setOwner(monster.getName());
		cout << "Player succesfully moved!\n";
	}
}

void Player::buyCards(EffectCard card,EffectCardDeck* deck)
{
	if (card.getCost() > energyCubes)
	{
		cout << "You can't buy this card, you don't have enough energy cubes.\n";
	}
	else
	{
		EffectCard returned = deck->pickCard(card.getName());
		if (returned.getName() == card.getName()) {
			cards.push_back(card);
			this->energyCubes = this->energyCubes - card.getCost();
			cout << "The card was purchased.\n";
		}
		else {
			cout << "This card does not currently exist in the deck of cards.\n";
		}
		
	}
}

void Player::addEnergyCubes(int i)
{
	this->energyCubes = energyCubes + i;
}


int Player::getHealth() const
{
	return monster.getHealth();
}

int Player::getVictoryPoints() const
{
	return monster.getVictoryPoints();
}

void Player::addHealth(int health)
{
	monster.addHealth(health);
}

void Player::removeHealth(int health)
{
	monster.removeHealth(health);
}

void Player::addPoints(int points)
{
	monster.addPoints(points);
}

void Player::removePoints(int points)
{
	monster.removePoints(points);
}

ostream & operator<<(ostream & os, const Player & player)
{
	return os<<player.monster;
}
