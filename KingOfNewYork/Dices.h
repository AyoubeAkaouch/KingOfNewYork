#pragma once

#include <map>
#include <vector>
using namespace std;

class Dices
{
private:
	map<int,map<int, string>> historyOffAllRolls; 
	map<int,string> currentDiceValues; // That could have been a vector
	const vector<string> possibleRolls{"Energy","Attack","Destruction","Heal","Celebrity","Ouch!"};
	int numberOfRolls=0;	//Used to keep track of roll history
	int numberOfRerolls = 0;	//Used to keep track of rerolls (Can't exceed 3)

	void updateHistory();
public:
	Dices();
	~Dices();
	void firstRoll();
	bool reroll(vector<int>* dicesToRoll); //Makes sure not to exceed number of rerolls
	void rollDices(vector<int>* dicesToRoll);
	vector<int> stringToVectorInt(string reRolls);
	map<int, string>* getCurrentValues();
	void showRollHistory();
	void applyEffect(string effect);
	friend ostream& operator<<(ostream& os, const Dices& dices);

};

