#pragma once

#include "GraphGeneric.h"
#include "Region.h"
#include "Player.h"

using namespace std;

class Player;

class GameMap
{
private: 
	GraphGeneric<Region> connectRegions;
	vector<Region> allRegions;
	string nameOfMap;
	string ownerSuperStar = "";
public:
	GameMap();
	GameMap(GraphGeneric<Region> connectRegion, string nameOfMap);
	~GameMap();
	GraphGeneric<Region> getMapGraph();
	string getNameMap();
	vector<Region>& getAllRegions();
	bool setOwnerRegion(string name,Region& region);
	void removeOwner(string name, Region& region);
	vector<string> getOwners(Region& region);
	void move(Player & player, Region & region);
	Player& getOwnerSuperStar(vector<Player>& players);
	void setOwnerSuperStar(Player& player, vector<Player>& players);
	friend ostream& operator<<(ostream & os, GameMap & gameMap);
};

