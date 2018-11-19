#include "ConcretePlayerObserver.h"



ConcretePlayerObserver::ConcretePlayerObserver()
{
}


ConcretePlayerObserver::~ConcretePlayerObserver()
{
}

void ConcretePlayerObserver::update(SubjectInterface* subject)
{
	Player* player = dynamic_cast<Player*>(subject); // Casting here because we need to pass SubjectInterface
	if (player == NULL) {
		cout << "You are unfortunately using the concrete player observer on an object different than a player, please register an appropriate observer to your player object" << endl;
	}
	else {
		cout << "~~~~~~~~~~~~~~~~~~~~~Player Observer~~~~~~~~~~~~~~~~~~~~~" << endl;

		if (player->getTurnPhase() == "diceRoll") {
			this->displayDiceRolling(player);
		}
		else if (player->getTurnPhase() == "resolvingDices") {
			this->displayResolveDices(player);
		}
		else if (player->getTurnPhase() == "move") {
			this->displayMove(player);
		}
		else if (player->getTurnPhase() == "buyCard") {
			this->displayBuyCards(player);
		}
		else if (player->getTurnPhase() == "endTurn") {
			this->displayEndOfTurn(player);
		}

		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	}
	

}

void ConcretePlayerObserver::displayDiceRolling(Player* player)
{
	cout << "Phase : Dice Rolling" << endl;
	cout << player->getName() << " just rolled these dices: " << player->getDices();
}

void ConcretePlayerObserver::displayResolveDices(Player* player)
{
	cout << "Phase : Resolving dices" << endl;
	cout << "The dices were resolved in this order: ";

	vector<string> resolved = player->getResolved();
	for (int i = 0; i < resolved.size(); i++) {
		cout << resolved[i] << "  ";
	}

	cout << endl;
}

void ConcretePlayerObserver::displayMove(Player* player)
{
	cout << "Phase : Moving " << endl;
	if (player->getMovedStatus()) {
		cout << player->getName() << " was moved and is now in this region: " << player->getRegion().getName() << endl;
	}
	else {
		cout << player->getName() << " was not moved and is still in : " << player->getRegion().getName() << endl;
	}
}

void ConcretePlayerObserver::displayBuyCards(Player* player)
{
	cout << "Phase: Buying cards" << endl;
	cout << player->getName() << " has a current energy balance of: " << player->getEnergyCubes() << endl;
	cout << player->getName() << " just finished the buy phase and he currently has these cards: " << endl;
	player->displayCards();
}

void ConcretePlayerObserver::displayEndOfTurn(Player* player)
{
	cout << "Phase: End of turn" << endl;
	cout << player->getName() << " currently has {" << player->getEnergyCubes() << " energy cubes} {" << player->getHealth() << " health points} {" << player->getVictoryPoints() << " victory points}" << endl;

	}
