#pragma once
#pragma once
#include <list>
#include "ObserverInterface.h"
using namespace std;

class ObserverInterface;
class SubjectInterface {
public:
	virtual void registerOb(ObserverInterface* ob) = 0;
	virtual void removeOb(ObserverInterface* ob) = 0;
	virtual void notifyOb() = 0;
};