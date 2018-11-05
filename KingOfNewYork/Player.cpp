#include "Player.h"
#include <iostream>

using namespace std;


Player::Player() : region(*(new Region()))
{
}

Player::Player(Monster monster) : region(*(new Region()))
{
	this->monster = monster;
	this->name = monster.getName();
	this->energyCubes = 0;
}

Player::Player(Monster monster, Region& region) : region(region)
{
	this->monster = monster;
	this->name = monster.getName();
	region.setOwner(monster.getName());
}

Player::~Player()
{
}

bool Player::RollDices(vector<int>* dicesToRoll) //For rerolls
{
	return dices.reroll(dicesToRoll);
	
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

map<int, string> Player::getCurrentValues()
{
	return dices.getCurrentValues();
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

Region& Player::getRegion()
{
	return this->region;
}

void Player::setRegion(Region& region)
{
	this->region = region;
}



bool Player::buyCards(EffectCard card)
{
	if (card.getCost() > energyCubes)
	{
		cout << "You can't buy this card, you don't have enough energy cubes.\n";
		return false;
	}
	else
	{
		
			cards.push_back(card);
			this->energyCubes = this->energyCubes - card.getCost();
			cout << "The card was purchased.\n";
			return true;
		
	}
}

void Player::addEnergyCubes(int i)
{
	this->energyCubes = energyCubes + i;
}

bool Player::removeEnergy(int i)
{
	if (energyCubes < i) {
		cout << "You do not have enough funds!" << endl;
		return false;
	}
	else {
		energyCubes = energyCubes - i;
		return true;
	}
}

int Player::getEnergyCubes()
{
	return energyCubes;
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
	if (getHealth() == 10) {
		cout << "Can't add more health, you are already at full health!" << endl;
	}
	else {
		monster.addHealth(health);
	}

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

bool Player::hasSuperStar()
{
	return superStar ;
}

void Player::setSuperStar(bool has)
{
	this->superStar = has;
}

ostream & operator<<(ostream & os, const Player & player)
{
	return os<<player.monster;
}
