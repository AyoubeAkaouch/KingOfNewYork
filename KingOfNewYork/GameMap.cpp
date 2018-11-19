#include "GameMap.h"



GameMap::GameMap()
{
}


GameMap::GameMap(GraphGeneric<Region> connectRegion, string nameOfMap)
{
	this->connectRegions = connectRegion;
	this->allRegions = connectRegion.getAllNodes();
	this->nameOfMap = nameOfMap;
}

GameMap::~GameMap()
{
	//Pleyers is deleted outside of the gameMap since it has been used in multiple places we can't let the GameMap handle it
}

GraphGeneric<Region> GameMap::getMapGraph()
{
	return connectRegions;
}

void GameMap::addPlayers(vector<Player*>* players)
{
	this->players = players;
}

string GameMap::getNameMap()
{
	return this->nameOfMap;
}
vector<Region>& GameMap::getAllRegions()
{
	return allRegions;
}

void GameMap::removeOwner(string name, Region& region)
{
	for (size_t i = 0; i < allRegions.size(); i++)
	{
		if (allRegions[i] == region)
			allRegions[i].removePlayer(name);
	}
}

bool GameMap::setOwnerRegion(string name,Region& region)
{
	for (size_t i = 0; i < allRegions.size(); i++)
	{
		if (allRegions[i] == region)
			return allRegions[i].setOwner(name);
	}
	return false;
}
vector<string> GameMap::getOwners(Region& region)
{
	for (size_t i = 0; i < allRegions.size(); i++)
	{
		if (allRegions[i] == region)
			return allRegions[i].getOwners();
	}
	cout << "This region does not exist in this map, returning empty vector"<<endl;
	return vector<string>();
}

void GameMap::move(Player& player, Region& region)
{
	//Check if move is possible
	if (player.getRegion().getName() == "")
	{
		player.setRegion(region);
		cout << "Player succesfully moved!\n";
	}
	else if (!(find(allRegions.begin(), allRegions.end(), region) != allRegions.end())) // If region doesnt exist
	{
		cout << "This is an illegal move\n";
	}
	else
	{
		if (region.setOwner(player.getName())) {
			player.getRegion().removePlayer(player.getName());
			player.setRegion(region);
			cout << "Player succesfully moved!\n";
		}
	}
}
Player & GameMap::getOwnerSuperStar(vector<Player*>& players)
{
	int currentOwner;
	//Do this to find current owner of superstar
	for (int i = 0; i < players.size(); i++) {
		if (players[i]->getName() == ownerSuperStar) {
			currentOwner = i;
			break;
		}
	}

	return *players[currentOwner];
}
void GameMap::setOwnerSuperStar(Player& player,vector<Player*>& players)
{
	if (ownerSuperStar == "") {
		ownerSuperStar = player.getName();
		player.setSuperStar(true);
	}
	else {
		int currentOwner;
		//Do this to find current owner of superstar
		for (int i = 0; i < players.size(); i++) {
			if (players[i]->getName() == ownerSuperStar) {
				currentOwner = i;
				break;
			}
		}

		//Removing ownership to the player before passing it to the new player
		players[currentOwner]->setSuperStar(false);
		ownerSuperStar = player.getName();
		player.setSuperStar(true);

	}
}


void GameMap::registerOb(ObserverInterface * ob)
{
	this->observers.push_back(ob);
}

void GameMap::removeOb(ObserverInterface * ob)
{
	for (int i = 0; i < observers.size(); i++) {
		if (observers[i] == ob) {
			observers.erase(observers.begin() + i);
			break;
		}
	}
}

void GameMap::notifyOb()
{
	for (int i = 0; i < observers.size(); i++) {
		observers[i]->update(this); //Passing the GameMap to make the observer aware of which GameMap got updated. 
	}
}

ostream & operator<<(ostream & os, GameMap & gameMap)
{
	vector<Region> regions = gameMap.getAllRegions();
	vector<Region> connections;
	vector<GraphGeneric<SubRegion>> subRegionsOfRegion;
	GraphGeneric<SubRegion> subRegionMap;
	GraphGeneric<Region> map = gameMap.getMapGraph();

	for (size_t i = 0; i < regions.size(); i++) {
		os << "Region: "<< regions[i] << endl;
		connections = map.getConnections(gameMap.allRegions[i]);
		subRegionsOfRegion = *regions[i].getSubRegions();
		if (connections.empty())
			os << "{}";
		else
		{
			os << "{";
			for (size_t j = 1; j < connections.size(); j++)//Start at 1 because 0 is the current region
			{
				os << connections[j];
				if (j < connections.size() - 1)
					os << ",";
			}
			os << "}"<< endl;
		}
		if (subRegionsOfRegion.size() == 0)
			os << "{}"<<endl;
		else
		{
			vector<SubRegion> allNodesSubRegion;
			os << "{";
			for (size_t j = 0; j < subRegionsOfRegion.size(); j++)
			{
				os << "{";
				subRegionMap = subRegionsOfRegion[j];
				allNodesSubRegion = subRegionMap.getAllNodes();
				for (size_t k = 0; k < allNodesSubRegion.size(); k++)
				{
					os << allNodesSubRegion[k];
					if (k < allNodesSubRegion.size() - 1)
						os << "->";
				}
				os << "}";
			}
			os << "}"<<endl;
		}



	}

	return os;
}
