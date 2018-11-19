#pragma once

#include "GraphGeneric.h"
#include "Region.h"
#include "Player.h"
#include "SubjectInterface.h"
#include "ObserverInterface.h"

using namespace std;

class Player;
class SubjectInterface;
class ObserverInterface;

class GameMap : public SubjectInterface
{
private: 
	GraphGeneric<Region> connectRegions;
	vector<Region> allRegions;
	string nameOfMap;
	string ownerSuperStar = "";
	vector<Player*>* players;

	vector<ObserverInterface*> observers;

public:
	GameMap();
	GameMap(GraphGeneric<Region> connectRegion, string nameOfMap);
	virtual ~GameMap();
	GraphGeneric<Region> getMapGraph();
	void addPlayers(vector<Player*>* players); // Have all the players stored in the GameMap.
	vector<Player*>* getPlayers();
	string getNameMap();
	vector<Region>& getAllRegions();
	bool setOwnerRegion(string name,Region& region);
	void removeOwner(string name, Region& region);
	vector<string> getOwners(Region& region);
	void move(Player & player, Region & region);
	Player& getOwnerSuperStar(vector<Player*>& players);
	void setOwnerSuperStar(Player& player, vector<Player*>& players);
	friend ostream& operator<<(ostream & os, GameMap & gameMap);

	//Methods of the observer
	virtual void registerOb(ObserverInterface* ob);
	virtual void removeOb(ObserverInterface* ob);
	virtual void notifyOb();
};

