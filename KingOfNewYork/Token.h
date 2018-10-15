#pragma once
#include <string>
using namespace std;

class Token
{
private:
	string name;
public:
	Token();
	Token(string name);
	string getName();
	~Token();
};

