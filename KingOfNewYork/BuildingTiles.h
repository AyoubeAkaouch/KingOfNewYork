#pragma once
#include <map>

using namespace std;

class BuildingTiles
{
private:
	int destroyPoints;
	map<string, int> rewardBuilding;//Will be of size 1
	map<string, int> rewardArmy;
	bool faceUp;
	bool destroyed;
	string name;
	string armyName;
public:
	BuildingTiles();
	BuildingTiles(string name);
	~BuildingTiles();
	string getName() const;
	map<string, int>* destroy(); //Destroys building/army and gives its reward.
	friend ostream & operator<<(ostream & os, const BuildingTiles & deck);
};

