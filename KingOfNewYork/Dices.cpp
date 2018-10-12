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
		cout << "Roll #"<< i <<": " << historyOffAllRolls.at(i)[0] << ", " << historyOffAllRolls.at(i)[1] << ", " << historyOffAllRolls.at(i)[2] << ", "
			<< historyOffAllRolls.at(i)[3] << ", " << historyOffAllRolls.at(i)[4] << ", " << historyOffAllRolls.at(i)[5] << endl;
	}

}

ostream & operator<<(ostream & os, const Dices & dices)
{
	os << "Current dices are: " << dices.currentDiceValues.at(0) << ", " << dices.currentDiceValues.at(1) << ", " << dices.currentDiceValues.at(2) << ", "
		<< dices.currentDiceValues.at(3) << ", " << dices.currentDiceValues.at(4) << ", " << dices.currentDiceValues.at(5) << endl;

	return os;
}
