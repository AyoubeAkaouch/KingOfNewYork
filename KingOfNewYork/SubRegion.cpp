#include "SubRegion.h"



SubRegion::SubRegion()
{
}

SubRegion::SubRegion(string owner)
{
	this->owner = owner;
}


SubRegion::~SubRegion()
{
}

void SubRegion::setOwner(string owner)
{
	this->owner = owner;
}

string SubRegion::getOwner()
{
	return owner;
}
