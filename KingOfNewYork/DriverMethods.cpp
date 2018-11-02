#include "DriverMethods.h"
#include "Player.h"
#include <vector>
#include <iostream>

using namespace std;

int firstPlayer(vector<Player> players) {
	int bestPlayerRollPosition=0, currentBestRoll=0, numberOfAttacks=0;
	vector<int> equalTopRolls; // Used to deal with equal rolls

	cout << "We are now determining who goes first!" << endl;

	for (int i = 0; i < players.size(); i++) {
		cout << players[i].getName() << " press Enter to roll your dices!" << endl;
		cin.get();
		map<int, string > current = players[i].RollDicesExtra();
		cout << players[i].getDices()<< endl;
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
			for (int j = 0; j < equalTopRolls.size(); j++) {
				equalTopRolls.erase(equalTopRolls.begin());
			}
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
		for (int j = 0; j < equalTopRolls.size(); j++) {
			equalTopRolls.erase(equalTopRolls.begin() + j);
		}

		for (int i = 0; i < rerolls.size(); i++) {
			cout << players[rerolls[i]].getName() << " press Enter to roll your dices!" << endl;
			cin.get();
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
				for (int j = 0; j < equalTopRolls.size(); j++) {
					equalTopRolls.erase(equalTopRolls.begin() + j);
				}
				equalTopRolls.push_back(rerolls[i]);
			}
			numberOfAttacks = 0; // Reseting our counter
		}
	}
	cout << players[bestPlayerRollPosition].getName() << " starts! Then the othersplay clockwise";

	return bestPlayerRollPosition;

}

void settingRegions(GameMap& gameMap, vector<Player> players, int currentTurn) {
	
	cout << "----------------" << endl;
	cout << gameMap;
	cout << "We are now setting up the pieces on the board!" << endl;
	for (int i = 0; i < players.size() ; i++ ) {
		
		cout << players[(i+currentTurn)%players.size()].getName() << "which region do you want to start in?"

	}
}

