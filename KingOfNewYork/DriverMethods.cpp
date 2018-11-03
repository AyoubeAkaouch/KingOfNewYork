#include "DriverMethods.h"
#include "Player.h"
#include "GameMap.h"
#include "Region.h"
#include <vector>
#include <iostream>

using namespace std;

int firstPlayer(vector<Player> players) {
	int bestPlayerRollPosition=0, currentBestRoll=0, numberOfAttacks=0;
	vector<int> equalTopRolls; // Used to deal with equal rolls

	cout << "~~~~~~~~~~~We are now determining who goes first!~~~~~~~~~~~" << endl << endl;

	for (int i = 0; i < players.size(); i++) {
		cout << players[i].getName() << " press Enter to roll your dices!" << endl;
		map<int, string > current = players[i].RollDicesExtra();
		cout << players[i].getDices() << endl << endl;
		for (int j = 0; j < current.size();j++) {
			
			if (current[j] == "Attack") {
				numberOfAttacks++;
			}
		}
		if (numberOfAttacks == currentBestRoll) {
			equalTopRolls.push_back(i);
		}
		else if (numberOfAttacks > currentBestRoll) {
			currentBestRoll = numberOfAttacks;
			bestPlayerRollPosition = i;

			//Clearing out this vector since no need to reroll
			equalTopRolls.clear();
			equalTopRolls.push_back(i);
		}
		numberOfAttacks = 0; // Reseting our counter
	}

	while (equalTopRolls.size() > 1)
	{
		cout << "\n~~~~Some players rolled the same number of Attacks and are tied for first turn!" << endl;
		cout << "Rerolls for players that are tied!" << endl << endl;
		vector<int> rerolls = equalTopRolls;
		//Restarting the values
		bestPlayerRollPosition = 0, currentBestRoll = 0, numberOfAttacks = 0;
		//Clearing out the equals!
		equalTopRolls.clear();

		for (int i = 0; i < rerolls.size(); i++) {
			cout << players[rerolls[i]].getName() << " press Enter to roll your dices!" << endl;
			//cin.get();
			map<int, string > current = players[rerolls[i]].RollDicesExtra();
			cout << players[rerolls[i]].getDices() << endl;
			for (int j = 0; j < current.size(); j++) {

				if (current[j] == "Attack") {
					numberOfAttacks++;
				}
			}
			
			if (numberOfAttacks == currentBestRoll) {
				equalTopRolls.push_back(rerolls[i]);
			}
			else if (numberOfAttacks > currentBestRoll) {
				currentBestRoll = numberOfAttacks;
				bestPlayerRollPosition = rerolls[i];

				//Clearing out this vector since no need to reroll
				equalTopRolls.clear();
				equalTopRolls.push_back(rerolls[i]);
			}
			numberOfAttacks = 0; // Reseting our counter
		}
	}
	cout << players[bestPlayerRollPosition].getName() << " starts! Then the others play clockwise" << endl;

	return bestPlayerRollPosition;

}

void settingRegions(GameMap& gameMap, vector<Player>& players, int currentTurn) {
	cout << "~~~~~~~~~~~~~We are now setting up the pieces on the board!~~~~~~~~~~~~~" << endl;
	cout << "--------------------------------MAP--------------------------------"<< endl << endl;
	cout << gameMap;

	vector<Region> availableRegion = gameMap.getAllRegions();
	int selectedRegion;
	bool isSet;

	//Showing the possible regions for him to go
	cout << "All the regions in this map: ";
	for (int i = 0; i < availableRegion.size();i++) {
		
		cout << i << ") " << availableRegion[i].getName() << " ";	
		
	}
	cout << endl;

	
	for (int i = 0; i < players.size() ; i++ ) {
		isSet = false;
		cout << players[(i + currentTurn) % players.size()].getName() << " which region do you want to start in (Choose by index)?"<<endl;
		while (!isSet) {
			cin >> selectedRegion;
			if (availableRegion[selectedRegion].getName() == "Manhattan") {
				cout << "A player can't select Manhattan as his staring region, Please select another one!" << endl;
			}
			else {
				isSet = gameMap.setOwnerRegion(players[(i + currentTurn) % players.size()].getName(), availableRegion[selectedRegion]);
				if (!isSet) {
					cout << "Select another region please." << endl;
				}
			}
		}
	}
}

