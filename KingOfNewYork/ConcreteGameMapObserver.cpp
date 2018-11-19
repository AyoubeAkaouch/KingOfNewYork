#include "ConcreteGameMapObserver.h"



ConcreteGameMapObserver::ConcreteGameMapObserver()
{
}


ConcreteGameMapObserver::~ConcreteGameMapObserver()
{
}

void ConcreteGameMapObserver::update(SubjectInterface * subject)
{
	GameMap* gameMap = dynamic_cast<GameMap*>(subject);
	if (gameMap == NULL) {
		cout << "You are unfortunately using the concrete GameMap observer on an object different than a GameMap, please register an appropriate observer to your GameMap object" << endl;
	}
	else {
		cout << "~~~~~~~~~~~~~~~~~~~~~GameMap Observer~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "Here are all the regions and their players:" << endl;
		vector<Region> regions = gameMap->getAllRegions();
		vector<Player*> players = *gameMap->getPlayers();
		//Going though all the regions
		for (int i = 0; i < regions.size(); i++) {
			
			cout << regions[i].getName() << ": ";
			
			vector<string> owners = regions[i].getOwners();
			//Going through all the owners to get their info
			for (int j = 0; j < owners.size(); j++) {
				//Matching the owner to the player object.
				for (int k = 0; k < players.size();k++) {
					//Print the number of victory points this player has.
					if (owners[j] == players[k]->getName())
					{
						cout << "{ " << owners[j] << " has " << players[k]->getVictoryPoints() << " victory points }";
					}
				}
			}
			//If there were no owners display this.
			if (owners.size() == 0) {
				cout << "No one currently in this region." << endl;
			}
			//If there are owners, add an endl since we did not have one when displaying the owners.
			else {
				cout << endl;
			}

		}
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	}

}
