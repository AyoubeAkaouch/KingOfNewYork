#include "ConcreteCardObserver.h"



ConcreteCardObserver::ConcreteCardObserver()
{
}


ConcreteCardObserver::~ConcreteCardObserver()
{
}

void ConcreteCardObserver::update(SubjectInterface * subject)
{
	EffectCard* card = dynamic_cast<EffectCard*>(subject);
	if (card == NULL) {
		cout << "You are unfortunately using the concrete card observer on an object different than a card, please register an appropriate observer to your card object" << endl;
	}
	else {
		cout << "~~~~~~~~~~~~~~~~~~~~~~~Card Observer~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout <<"Using: " << card->getName() << endl;
		cout << "Effect: " << card->getDescription() << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	}

}
