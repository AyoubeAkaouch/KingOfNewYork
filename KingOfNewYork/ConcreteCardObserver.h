#pragma once
#include "ObserverInterface.h"
#include "SubjectInterface.h"
#include "EffectCard.h"
#include <iostream>

class ConcreteCardObserver :
	public ObserverInterface
{
public:
	ConcreteCardObserver();
	virtual ~ConcreteCardObserver();
	virtual void update(SubjectInterface* subject);
};

