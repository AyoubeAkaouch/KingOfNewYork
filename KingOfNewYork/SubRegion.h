#pragma once

#include <string>
using namespace std;

class SubRegion
{
public:
	SubRegion();
	SubRegion(string owner);
	~SubRegion();
	void setOwner(string owner);//Change this to player when implemented
	string getOwner();
private:
	string owner;//Change this to player when implemented
	
};


