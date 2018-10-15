#include "Monster.h"



Monster::Monster(string name)
{
	this->name = name;
	this->hp = 10;
	this->vp = 0;

}


Monster::~Monster()
{
}

string Monster::getName() const
{
	return name;
}

int Monster::getHealth() const
{
	return hp;
}

int Monster::getVictoryPoints() const
{
	return vp;
}

void Monster::addHealth(int health)
{
	hp = hp + health;
}

void Monster::removeHealth(int health)
{
	hp = hp - health;
}

void Monster::addPoints(int points)
{
	vp = vp + points;
}

void Monster::removePoints(int points)
{
	vp = vp - points;
}

ostream & operator<<(ostream & os, const Monster & monster)
{
	os << "{Monster " << monster.name << " has " << monster.hp << " health points and " << monster.vp << " victory points.}\n";
	return os;
}
