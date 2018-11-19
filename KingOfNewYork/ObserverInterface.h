#pragma once
#include "SubjectInterface.h"

class SubjectInterface;

class ObserverInterface {

public:
	virtual void update(SubjectInterface* subject) = 0; 
	/* Want to have same observer for all players. By passing the subject instead of storing it inside the observer 
	we can tell the observer which player has been updated instead of having an observer created for each player.
	*/
};