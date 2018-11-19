#include "StrategyPlayerInterface.h"

class BalancedPlayerStrategy : public StrategyPlayerInterface {
public:

	/*
		The aggressive player strategy will have this player profile:
			- During dice rolls : Will reroll anything that is not Heal or Attack.
			- Resolve dices : Will just resolve in whatever order the dices are returned.
			- Move : Will always stay in  Manhattan.
			- Buy cards: Will always try to buy a card.
	*/
	BalancedPlayerStrategy() {}
	virtual ~BalancedPlayerStrategy() {}


	virtual bool move(Player & player, GameMap & gameMap, bool gotAttacked) override {

		vector<Region> availableRegion = gameMap.getAllRegions();
		int indexManhattan;
		char changeRegion;
		int selectedRegion;
		bool wasMoved = false;
		for (int i = 0; i < availableRegion.size(); i++) {
			if (availableRegion[i].getName() == "Manhattan") {
				indexManhattan = i;
			}
		}


		//If no one in manhattan, move player there!
		if (availableRegion[indexManhattan].getOwners().empty()) {
			gameMap.removeOwner(player.getName(), player.getRegion());// Removing player from his current Region
			gameMap.setOwnerRegion(player.getName(), availableRegion[indexManhattan]); // Adding him to new region
			player.setRegion(availableRegion[indexManhattan]); // Pointing to new region where player is
			cout << "No one currently in Manhattan, you were placed in Manhattan, you unfortunately have no choice!" << endl;
			player.addPoints(1);
			player.addEnergyCubes(2);
			wasMoved = true;
		}
		//If already in manhattan, move player one level upper
		else if (player.getRegion().getName() == "Manhattan" && !gotAttacked) {
			cout << "You are currently in Manhattan, you can't change boroughs but you are moving one space up inside of Manhattan!" << endl;
			player.addPoints(2);
			player.addEnergyCubes(2);
		}
		//If in Manhattan and got attacked player stays here.
		else if (player.getRegion().getName() == "Manhattan" && gotAttacked) {
			Region currentRegionName = player.getRegion();
			cout << "Oh no! Another player attacked you :( Would you like to move to a different borough outside of Manhattan?(y/n)" << endl;
			cout << "Balanced player will stay in Manhattan" << endl;
			
		}
		//A player in a normal borough is asked if he wants to move
		else {
			cout << "Would you like to change boroughs?(y/n)" << endl;
			cout << "Balanced player will stay in the same borough automatically." << endl;
		}

		return wasMoved;
	}

	virtual vector<string> resolveDices(Player & player, GameMap& gameMap, vector<Player*> & players) override
	{

		cout << "Automatically resolving all the rolled dices!" << endl;

		string toResolve;
		vector<string> sameToResolve;
		vector<string> resolved; // Since we are getting a pointer we can't erase from map what has already been resolve, it wil change dice object.
		map<int, string> currentDices = player.getCurrentValues();
		int dicesResolved = 0;
		for (int j = 0; j < currentDices.size(); j++) //Until all dices are resolved
		{
			toResolve = currentDices.at(j);
			for (int i = 0; i < currentDices.size(); i++)
			{
				if (currentDices.at(i) == toResolve && !(find(resolved.begin(), resolved.end(), toResolve) != resolved.end()))
				{
					sameToResolve.push_back(toResolve);
					dicesResolved++;
				}
			}
			applyDiceEffect(sameToResolve, player, gameMap, players); //applying on a vector to apply all effect at the same time.
			sameToResolve.clear(); // So that we can do this again with next effect we wish to apply.
			resolved.push_back(toResolve);
		}

		return resolved;
	}

	virtual void diceRoll(Player & player, bool extraDices) override
	{
		bool canRoll = true;
		char rollAgain = 'n';
		vector<int> toReroll;


		if (extraDices) {
			player.RollDicesExtra();
		}
		else {
			player.RollDices();
		}


		cout << "Here is the first roll :\n" << player.getDices();
		map<int, string> currentDices = player.getDices().getCurrentValues();


		while (canRoll)
		{
			rollAgain = 'n';//Having it default to no reroll until we check if a reroll is necessary. If all dices are attack or desrtrruction no need to reroll!

			//Here we check if we have at least on dice that is not attack or destruction to see if we proceed with a reroll
			for (int i = 0; i < currentDices.size(); i++) {

				if (currentDices.at(i) == "Heal" || currentDices.at(i) == "Attack") {
					//Do nothing we keep them
				}
				else {
					rollAgain = 'y';
					break;
				}
			}

			//If decides to roll again go through de reroll process
			if (rollAgain == 'y')
			{
				cout << "Balanced player will automatically reroll anything that is not Heal or Attack" << endl;
				//Going through all possible dices and if it is not a destrction or attack reroll it.
				for (int i = 0; i < currentDices.size(); i++) {

					if (currentDices.at(i) == "Heal" || currentDices.at(i) == "Attack") {
						//Do nothing we keep them
					}
					else {
						toReroll.push_back(i);
					}
				}

				cout << "Rerolled dices are the following: ";
				for (int i = 0; i < toReroll.size(); i++) {
					cout << toReroll[i] << "  ";
				}

				cout << endl;
				canRoll = player.RollDices(&toReroll);
				toReroll.clear(); // Clearing to have an empty vector if there is another set of rerolls
				cout << "\nHere are your current dices:\n" << player.getDices();
				currentDices = player.getCurrentValues();
			}
			else
			{
				break;
			}
		}

	}

	virtual void buyCards(Player & player, vector<EffectCard>& buyableCards, EffectCardDeck & effectCards)
	{
		bool done = false;
		cout << "Aggressive player now checking if he will buy a card or not." << endl;

		cout << "Here are the 3 cards that you can buy:" << endl;
		for (int i = 0; i < buyableCards.size(); i++) {
			cout << i << ") " << buyableCards[i] << endl;
		}

		//Going over the possible cards and buying the first card the player can get.
		//If no cards were bought pay 2 energy if possible to change all cards.
		for (int i = 0; i < buyableCards.size(); i++) {
			if (buyableCards[i].getCost() < player.getEnergyCubes()) {
				done = player.buyCards(buyableCards[i]);
				buyableCards.erase(buyableCards.begin() + i);
				buyableCards.push_back(effectCards.draw());
				cout << "The card you bought got replaced by this one: " << endl;
				cout << buyableCards[2] << endl;
				break;
			}
		}

		//If we could not buy a card redraw new 3 cards
		if (!done) {
			if (player.getEnergyCubes() >= 2) {
				done = true;
				buyableCards.clear();
				for (int i = 0; i < 3; i++) {
					buyableCards.push_back(effectCards.draw());
				}
				cout << "Here are the 3 new cards:" << endl;
				for (int i = 0; i < buyableCards.size(); i++) {
					cout << i << ") " << buyableCards[i] << endl;
				}

			}
		}

		if (!done) {
			cout << player.getName() << " could not do anything during the buying phase, now going to the next phase." << endl;
		}

	}


private:
	void applyDiceEffect(vector<string> effect, Player& player, GameMap& gameMap, vector<Player*> & players) {
		//For all the if statement only checking the first index because we can't pass an empty vector!

		if (effect.empty()) {
			//cout << "There was a typo please retry" << endl;
		}
		//Applying celebrity dices
		else if (effect[0] == "Celebrity") {
			if (player.hasSuperStar()) {
				//When player has superstar card every celebrity roll gets him +1 victory pt 
				player.addPoints(effect.size());
				cout << player.getName() << " just gained " << effect.size() << " victory points because of his superstar card." << endl;
			}
			//If player does not have the superstar card he can aquire it here if 3+ celebrity.
			else {
				if (effect.size() < 3) {
					cout << "Sorry but these celebrity dices do not have any effects you don't have enough or you dont have the superstar card!" << endl;
				}
				//Player aquires the superstar card and gets 1 victory points + 1 per extra celebirty;
				else {
					gameMap.setOwnerSuperStar(player, players);
					player.addPoints(effect.size() - 2);
					cout << player.getName() << " just gained " << effect.size() - 2 << " victory points and gained the superstar card." << endl;
				}
			}
		}

		//Applying attack dices
		else if (effect[0] == "Attack") {
			//apply damage to everyone outside of manhattan if in manhattan
			if (player.getRegion().getName() == "Manhattan") {
				for (int i = 0; i < players.size(); i++) {
					if (players[i]->getRegion().getName() != "Manhattan")
					{
						players[i]->removeHealth(effect.size());
						cout << players[i]->getName() << " just lost " << effect.size() << " health by being attacked." << endl;
					}
				}
			}
			//Apply damage to every monster in manhattan if you are not in Manhattan 
			else {
				bool noOneInManhattan = true;
				for (int i = 0; i < players.size(); i++) {
					if (players[i]->getRegion().getName() == "Manhattan")
					{
						noOneInManhattan = false;
						players[i]->removeHealth(effect.size());
						cout << players[i]->getName() << " just lost " << effect.size() << " health by being attacked." << endl;
						players[i]->move(*players[i], gameMap, true);
					}
				}
				//If no one in manhattan the attack dices had no effect
				if (noOneInManhattan) {
					cout << "No one was in Manhattan! The Attack dices did not impact anyone!" << endl;
				}
			}
		}
		else if (effect[0] == "Energy") {
			player.addEnergyCubes(effect.size());
			cout << player.getName() << " just gained " << effect.size() << " energy cubes." << endl;
		}
		else if (effect[0] == "Heal") {
			int addedHealth;
			if ((player.getHealth() + effect.size()) > 10) {
				addedHealth = 10 - player.getHealth();
			}
			else {
				addedHealth = effect.size();
			}
			player.addHealth(addedHealth);
			cout << player.getName() << " just gained " << addedHealth << " health points." << endl;

		}
	}


};