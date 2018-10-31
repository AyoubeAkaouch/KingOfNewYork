#include "Dices.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>


using namespace std;

Dices::Dices()
{
	firstRoll();
}


Dices::~Dices()
{
}

void Dices::updateHistory()
{
	historyOffAllRolls[numberOfRolls] = currentDiceValues;
	numberOfRolls++;
}

void Dices::firstRoll()
{
	vector<int> fullReroll = { 0,1,2,3,4,5 };
	numberOfRerolls = 0;
	numberOfDices = 6;
	rollDices(&fullReroll);
}

void Dices::firstRollExtra()
{
	vector<int> fullReroll = { 0,1,2,3,4,5,6,7 };
	numberOfRerolls = 0;
	numberOfDices = 8;
	rollDices(&fullReroll);
}

bool Dices::reroll(vector<int>* dicesToRoll)
{
	numberOfRerolls++;
	if (numberOfRerolls==2) 
	{
		rollDices(dicesToRoll);
		cout << "You have now exceeded you number of Rerolls" <<endl;
		return false;
	}
	else if (numberOfRerolls > 2)
	{
		cout << "You have now exceeded you number of Rerolls" << endl;
		return false;
	}
	else
	{
		rollDices(dicesToRoll);
		return true;
	}
}
void Dices::rollDices(vector<int>* dicesToRoll)
{
	int diceToChange;
	for (int i=0;i<dicesToRoll->size();i++)
	{
		diceToChange = dicesToRoll->at(i);
		currentDiceValues[diceToChange] = possibleRolls[rand()%6];
	}
	if (numberOfDices<currentDiceValues.size()) {
		currentDiceValues.erase(6);
		cout << "asdfghjkl\n";
		currentDiceValues.erase(7);
	}
	updateHistory();
}


vector<int> Dices::stringToVectorInt(string reRolls)
{
	stringstream iss(reRolls);
	int number;
	vector<int> myNumbers;


	while (iss >> number)
		myNumbers.push_back(number);
	return myNumbers;
}

map<int, string>* Dices::getCurrentValues()
{
	return &currentDiceValues;
}

void Dices::showRollHistory()
{
	cout << "~~~~~~~~~~~~~~~Roll History~~~~~~~~~~~~~~~" << endl;
	for (int i =0; i<historyOffAllRolls.size(); i++)  
	{
		cout << "Roll #: "<< i+1 << ": ";
		for (int j = 0; j < historyOffAllRolls.at(i).size(); j++)
		{
			if (j == historyOffAllRolls.at(i).size() - 1) {
				cout << historyOffAllRolls.at(i)[j] << endl;
			}
			else {
				cout << historyOffAllRolls.at(i)[j] << ", ";
			}
		}
		
	}

}

void Dices::applyEffect(string effect)
{
	//Currently empty will code in next assignment
	cout << "Applied " << effect << " .\n";
}

ostream & operator<<(ostream & os, const Dices & dices)
{
	os << "Current dices are: ";
	for (int i = 0; i < dices.currentDiceValues.size(); i++)
	{
		if (i == dices.currentDiceValues.size() - 1) {
			os << dices.currentDiceValues.at(i) << endl;
		}
		else {
			os << dices.currentDiceValues.at(i) << ", ";
		}
		
	}

	return os;
}
