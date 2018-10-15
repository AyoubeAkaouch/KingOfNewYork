#pragma once
#include <string>

using namespace std;
class Card
{
private: 
	string name;
public:
	Card();
	Card(string name);
	~Card();
	virtual string getName() = 0;
	friend ostream & operator<<(ostream & os, const Card & card);
};

