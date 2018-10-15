#include "Card.h"

using namespace std;

Card::Card() 
{
	name = "";
}
Card::Card(string name)
{
	this->name=name;
}


Card::~Card()
{
}

string Card::getName()
{
	return name;
}

ostream & operator<<(ostream & os, const Card & card)
{
	os << "x";
	return os; //Implemented in the real cards (monster,buildingtiles,effectscards)
}
