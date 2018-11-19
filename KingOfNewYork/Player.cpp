#include "Player.h"
#include <iostream>

using namespace std;


Player::Player() : region(*(new Region()))
{
}

Player::Player(Monster monster, StrategyPlayerInterface* playerBehaviour) : region(*(new Region()))
{
	this->monster = monster;
	this->name = monster.getName();
	this->energyCubes = 0;
	this->playerBehaviour = playerBehaviour;
	this->turnPhase = "diceRoll";
	this->wasMoved = false;
}

Player::Player(Monster monster, Region& region, StrategyPlayerInterface* playerBehaviour) : region(region)
{
	this->monster = monster;
	this->name = monster.getName();
	region.setOwner(monster.getName());
	this->playerBehaviour = playerBehaviour;
	this->energyCubes = 0;
	this->turnPhase = "diceRoll"; // Setting it to diceRoll since it is the first step a turn starts by.
	this->wasMoved = false;
}

Player::~Player()
{
	//Since we have a pointer we have to make sure it has been deleted before destroying object.
	delete playerBehaviour;
	//Not destroying the observers since we using the same ones for all players
}

bool Player::RollDices(vector<int>* dicesToRoll) //For rerolls
{
	bool canReroll = dices.reroll(dicesToRoll);
	//Notfying observers here instead of in thediceRoll method to update whenever dices are rolled!
	this->notifyOb();
	return canReroll;
	
}


map<int, string> Player::RollDices()
{
	dices.firstRoll();
	//Notfying observers here instead of in thediceRoll method to update whenever dices are rolled!
	this->notifyOb();
	return dices.getCurrentValues();
}

map<int, string> Player::RollDicesExtra()
{
	dices.firstRollExtra();
	//Notfying observers here instead of in thediceRoll method to update whenever dices are rolled!
	this->notifyOb();
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

string Player::getTurnPhase()
{
	return this->turnPhase;
}

vector<string> Player::getResolved()
{
	return this->resolved;
}

bool Player::getMovedStatus() {
	return this->wasMoved;
}

StrategyPlayerInterface * Player::getPlayerBehaviour()
{
	return this->playerBehaviour;
}

void Player::move(Player & player, GameMap & gameMap, bool gotAttacked)
{
	this->turnPhase = "move";
	wasMoved = playerBehaviour->move(player, gameMap, gotAttacked);
	this->notifyOb();
}

void Player::resolveDices(Player & player, GameMap & gameMap, vector<Player*>& players)
{
	this->turnPhase = "resolvingDices";
	this->resolved = playerBehaviour->resolveDices(player, gameMap, players);
	this->notifyOb();
}

void Player::diceRoll(Player & player, bool extraDices)
{
	this->turnPhase = "diceRoll";
	playerBehaviour->diceRoll(player,extraDices);
	//Not notifying here since we are notifying in other methods
}

void Player::buyCards(Player & player, vector<EffectCard>& buyableCards, EffectCardDeck & effectCards)
{
	this->turnPhase = "buyCard";
	playerBehaviour->buyCards(player,buyableCards,effectCards);
	this->notifyOb();
	turnPhase = "endTurn"; //Having this right here because after buying cards the turn is finished
	this->notifyOb(); // Now observer knows that it is the end of the urn and will display final info.
}

void Player::registerOb(ObserverInterface * ob)
{
	this->observers.push_back(ob);
}

void Player::removeOb(ObserverInterface * ob)
{
	for (int i = 0; i < observers.size(); i++) {
		if (observers[i] == ob) {
			observers.erase(observers.begin()+i);
			break;
		}
	}
}

void Player::notifyOb()
{
	for (int i = 0; i < observers.size();i++) {
		observers[i]->update(this); //Passing the player to make the observer aware of which player got updated. 
	}
}

ostream & operator<<(ostream & os, const Player & player)
{
	return os<<player.monster;
}
