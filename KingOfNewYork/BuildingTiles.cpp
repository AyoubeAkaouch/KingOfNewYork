#include "BuildingTiles.h"
#include <iostream>
#include <string>

using namespace std;


BuildingTiles::BuildingTiles()
{
}

BuildingTiles::BuildingTiles(string name)
{
	this->faceUp = true;
	this->name = name;
	this->destroyed = false;
	if (name =="Building1")
	{
		this->destroyPoints = 1;
		this->rewardBuilding["Victory"] = 1;
		this->rewardArmy["Health"] = 1;
		this->armyName = "Infantry";
	}
	else if (name=="Building2")
	{
		this->destroyPoints = 2;
		this->rewardBuilding["Victory"] = 2;
		this->rewardArmy["Energy"] = 2;
		this->armyName = "Jet";
	}
	else if (name =="Building3")
	{
		this->destroyPoints = 3;
		this->rewardBuilding["Victory"] = 3;
		this->rewardArmy["Victory"] = 3;
		this->armyName = "Tank";
	}
	else if (name == "Hospital2")
	{
		this->destroyPoints = 2;
		this->rewardBuilding["Health"] = 2;
		this->rewardArmy["Energy"] = 2;
		this->armyName = "Jet";
	}
	else if (name == "Hospital3")
	{
		this->destroyPoints = 3;
		this->rewardBuilding["Health"] = 3;
		this->rewardArmy["Victory"] = 3;
		this->armyName = "Tank";
	}
	else if (name == "Plant2")
	{
		this->destroyPoints = 2;
		this->rewardBuilding["Energy"] = 2;
		this->rewardArmy["Energy"] = 2;
		this->armyName = "Jet";
	}
	else if (name == "Plant 3")
	{
		this->destroyPoints = 3;
		this->rewardBuilding["Energy"] = 3;
		this->rewardArmy["Victory"] = 3;
		this->armyName = "Tank";
	}
}


BuildingTiles::~BuildingTiles()
{
}

string BuildingTiles::getName() const
{
	return name;
}

map<string, int>* BuildingTiles::destroy()
{
	if (destroyed)
	{
		cout << "Building is completely destroyed it shouldn't be on your current board." << endl;
		return nullptr;
	}
	if (faceUp)
	{
		faceUp = false;
		return &rewardBuilding;
	}
	else
	{
		destroyed = true;
		return &rewardArmy;
	}
}

ostream & operator<<(ostream & os, const BuildingTiles & tile)
{
	os << "{Building type: " << tile.name << endl;
	for (auto& it : tile.rewardBuilding)
	{
		os << "Building effect: " << it.second << " " << it.first << ".\n";
	}
	os << "Army type: "<< tile.armyName << endl;
	for (auto& it : tile.rewardArmy)
	{
		os << "Army effect: " << it.second << " " << it.first << ".}\n";
	}
	return os;	
}
