#pragma once
#include "ObserverInterface.h"
#include "SubjectInterface.h"
#include "GameMap.h"
#include "Player.h"

class GameMap;
class SubjectInterface;
/*
	Whenever a player changes boroughs this here gets called to show the user the updated map.
*/
class ConcreteGameMapObserver :
	public ObserverInterface
{
public:
	ConcreteGameMapObserver();
	virtual ~ConcreteGameMapObserver();
	virtual void update(SubjectInterface* subject);
};

