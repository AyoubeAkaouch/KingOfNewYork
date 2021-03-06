#pragma once
#include "ObserverInterface.h"
#include "SubjectInterface.h"
#include "Player.h"

class Player;
class SubjectInterface;
/*
	Whenever the player completes a new phase this gets called to show the new state of the object after completing said phase.
*/
class ConcretePlayerObserver :
	public ObserverInterface
{
public:
	ConcretePlayerObserver();
	virtual ~ConcretePlayerObserver();
	virtual void update(SubjectInterface* subject);
private:
	void displayDiceRolling(Player* player);
	void displayResolveDices(Player* player);
	void displayMove(Player* player);
	void displayBuyCards(Player* player);
	void displayEndOfTurn(Player* player);
};

