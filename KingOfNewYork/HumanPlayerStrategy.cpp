#include "StrategyPlayerInterface.h"
#include <sstream>


class HumanPlayerStrategy : public StrategyPlayerInterface {
public:

	/*
		The aggressive player strategy will have this player profile:
			- During dice rolls : Will reroll anything that is not Heal or Attack.
			- Resolve dices : Will just resolve in whatever order the dices are returned.
			- Move : Will always stay in  Manhattan.
			- Buy cards: Will always try to buy a card.
	*/
	HumanPlayerStrategy() {}
	virtual ~HumanPlayerStrategy() {}


	virtual bool move(Player & player, GameMap & gameMap, bool gotAttacked)
	{
		vector<Region> availableRegion = gameMap.getAllRegions();
		int indexManhattan;
		char changeRegion;
		int selectedRegion;
		bool wasMoved=false;
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
			wasMoved = true;
		}
		//If already in manhattan, move player one level upper
		else if (player.getRegion().getName() == "Manhattan" && !gotAttacked) {
			cout << "You are currently in Manhattan, you can't change boroughs but you are moving one space up inside of Manhattan!" << endl;
		}
		//If in Manhattan and got attacked offer the player to move somewhere else.
		else if (player.getRegion().getName() == "Manhattan" && gotAttacked) {
			Region currentRegionName = player.getRegion();
			cout << "\n\nOh no! Another player attacked you :( Would you like to move to a different borough outside of Manhattan?(y/n)" << endl;
			cin >> changeRegion;
			if (changeRegion == 'y') {
				//Showing the possible regions for him to go
				cout << "All the regions in this map: ";
				for (int i = 0; i < availableRegion.size(); i++) {

					cout << i << ") " << availableRegion[i].getName() << " ";

				}
				cout << endl;


				bool isSet = false;

				cout << player.getName() << " which region do you want to go to (Choose by index)?" << endl;
				while (!isSet) {
					cin >> selectedRegion;
					if (availableRegion[selectedRegion].getName() == "Manhattan") {
						cout << "You can't choose Manhattan again sorry!" << endl;
						cout << "Select another region please." << endl;
					}
					else {
						isSet = gameMap.setOwnerRegion(player.getName(), availableRegion[selectedRegion]);
						if (!isSet) {
							cout << "Select another region please." << endl;
						}
					}
				}
				wasMoved = true;
				gameMap.removeOwner(player.getName(), player.getRegion());// Removing player from his current Region
				player.setRegion(availableRegion[selectedRegion]);
				cout << player.getName() << " was moved to " << availableRegion[selectedRegion].getName() << endl;
				cout << "Manhattan is now empty watch out!\n\n" << endl;

			}
			else {
				cout << "Alright! " << player.getName() << " stays in Manhattan" << endl;
			}
		}
		//A player in a normal borough is asked if he wants to move
		else {
			cout << "Would you like to change boroughs?(y/n)" << endl;
			cin >> changeRegion;
			if (changeRegion == 'y') {
				//Showing the possible regions for him to go
				cout << "All the regions in this map: ";
				for (int i = 0; i < availableRegion.size(); i++) {

					cout << i << ") " << availableRegion[i].getName() << " ";

				}
				cout << endl;


				bool isSet = false;
				cout << player.getName() << " you are now currently in " << player.getRegion().getName() << endl;
				cout << player.getName() << " which region do you want to go to (Choose by index)?" << endl;
				while (!isSet) {
					cin >> selectedRegion;
					if (availableRegion[selectedRegion].getName() == "Manhattan") {
						cout << "You can't choose Manhattan sorry!" << endl;
					}
					else if (availableRegion[selectedRegion].getName() == player.getRegion().getName()) {
						cout << "You are already in this region! This is not a legal move." << endl;
					}
					else {
						isSet = gameMap.setOwnerRegion(player.getName(), availableRegion[selectedRegion]);
						if (!isSet) {
							cout << "Select another region please." << endl;
						}
					}
				}
				wasMoved = true;
				gameMap.removeOwner(player.getName(), player.getRegion());// Removing player from his current Region
				player.setRegion(availableRegion[selectedRegion]);
				cout << player.getName() << " was moved to " << availableRegion[selectedRegion].getName() << endl;
			}
		}


		return wasMoved;
	}

	virtual vector<string> resolveDices(Player & player, GameMap& gameMap, vector<Player*> & players)
	{
		string toResolve;
		vector<string> sameToResolve;
		vector<string> resolved; // Since we are getting a pointer we can't erase from map what has already been resolve, it wil change dice object.
		map<int, string> currentDices = player.getCurrentValues();
		int dicesResolved = 0;

		//Seeing if player has 2 extra attacks
		vector<EffectCard*> cards = player.getCards();
		for (int i = 0; i < cards.size(); i++) {
			if (cards[i]->getName() == "Towering Titan") {
				currentDices.insert({ (currentDices.size()),"Attack" });
				currentDices.insert({ (currentDices.size()),"Attack" });
				cards[i]->useCard();
			}
		}

		//Seeing if player has 1 extra destruction
		for (int i = 0; i < cards.size(); i++) {
			if (cards[i]->getName() == "Stomp") {
				currentDices.insert({ (currentDices.size()),"Destruction" });
				cards[i]->useCard();
			}
		}

		while (dicesResolved < 6) //Until all dices are resolved
		{
			cout << "Which effect you want to apply?\n";
			cin >> toResolve;
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


	virtual void diceRoll(Player & player, bool extraDices)
	{
		bool canRoll = true;
		char rollAgain;
		vector<int> toReroll;


		if (extraDices) {
			player.RollDicesExtra();
		}
		else {
			player.RollDices();
		}


		//cout << "Here is the first roll :\n" << player.getDices();
		while (canRoll)
		{
			cout << "Would you like to roll again (y/n)?" << endl;
			cin >> rollAgain;
			if (rollAgain == 'y')
			{
				cout << "Which dices you which to roll again (Input the dice positions with a space in between)?" << endl;
				string line;
				getline(cin, line);
				getline(cin, line);
				toReroll = stringToVectorInt(line);

				canRoll = player.RollDices(&toReroll);
				//Taken care of in player observer				  
				//cout << "\nHere are your current dices:\n" << player.getDices();
			}
			else
			{
				break;
			}
		}

	}
	

	virtual void buyCards(Player & player, vector<EffectCard*>& buyableCards, EffectCardDeck & effectCards)
	{
		char input;
		int input2;
		bool done = false;
		cout << "Would you like to buy a card? (y/n)" << endl;
		cin >> input;
		if (input == 'y') {
			cout << "Here are the cards that you can buy:" << endl;
			for (int i = 0; i < buyableCards.size(); i++) {
				cout << i << ") " << *buyableCards[i] << endl;
			}
			while (!done) {
				cout << "Your current balance is: " << player.getEnergyCubes() << endl;
				cout << "Choose card you wish to buy by index, press 3 to pay 2 energies and get 3 new cards, press 4 to quit buying." << endl;
				cin >> input2;
				if (input2 >= 0 && input2 <= 2) {
					done = player.buyCards(buyableCards[input2]);
					if (done) {
						buyableCards.erase(buyableCards.begin() + input2);
						if (effectCards.sizeOfDeck() >= 1) {
							buyableCards.push_back(effectCards.draw());
							cout << "The card you bought got replaced by this one: " << endl;
							cout << *buyableCards[buyableCards.size() - 1] << endl;
						}
						else {
							cout << "The deck is empty no cards added to the buyable cards" << endl;
						}

					}
				}
				else if (input2 == 3) {
					if (player.getEnergyCubes() >= 2 && effectCards.getAllCards().size()>2) {
						done = true;
						player.removeEnergy(2);
						buyableCards.clear();
						for (int i = 0; i < 3; i++) {
							buyableCards.push_back(effectCards.draw());
						}
						cout << "Here are the 3 cards that you can buy:" << endl;
						for (int i = 0; i < buyableCards.size(); i++) {
							cout << i << ") " << *buyableCards[i] << endl;
						}

					}
					else if (effectCards.getAllCards().size() > 0) {
						if (!done && player.getEnergyCubes() >= 2) {
							done = true;
							buyableCards.clear();
							int sizeOfDeck = effectCards.sizeOfDeck();
							for (int i = 0; i < sizeOfDeck; i++) {
								buyableCards.push_back(effectCards.draw());
							}
							cout << "Here are the new cards:" << endl;
							for (int i = 0; i < buyableCards.size(); i++) {
								cout << i << ") " << *buyableCards[i] << endl;
							}

						}
					}
					else {
						cout << "Can't replace these cards! Please choose another option" << endl;
					}
				}
				else if (input2 == 4) {
					cout << "Exiting the buying sequence!" << endl;
					done = true;
				}
			}

		}

	}

private:
	void applyDiceEffect(vector<string> effect, Player& player, GameMap& gameMap, vector<Player*> & players) {
		//For all the if statement only checking the first index because we can't pass an empty vector!

		if (effect.empty()) {
			cout << "There was a typo please retry" << endl;
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
					//Attacking players not in manhattan AND that are not already dead and removed from the game (health points > 0)
					if (players[i]->getRegion().getName() != "Manhattan" && players[i]->getHealth() > 0)
					{
						int damageDealt = effect.size();
						vector<EffectCard*> cards = player.getCards();

						//Check if attacked player has Shadow Double card, then remove 2 energy from the attacker
						for (int j = 0; j < cards.size(); j++) {
							if (cards[j]->getName() == "Shadow Double") {
								cards[j]->useCard();
								damageDealt += effect.size();
							}

						}

						//Check if attacked player has Tesla Antennae card, then remove 2 energy from the attacker
						for (int j = 0; j < cards.size(); j++) {
							//If player has the card and less health than opponent, deal 1 extra damage
							if (cards[j]->getName() == "Tesla Antennae" && (player.getHealth() < players[i]->getHealth())) {
								cards[j]->useCard();
								damageDealt++;
							}

						}

						players[i]->removeHealth(damageDealt);

						vector<EffectCard*> cardsAttacked = players[i]->getCards();
						//Check if attacked player has Drain card, then remove 2 energy from the attacker
						for (int j = 0; j < cardsAttacked.size(); j++) {
							if (cardsAttacked[j]->getName() == "Drain") {
								cardsAttacked[j]->useCard();
								if (player.getEnergyCubes() >= 2) {
									player.removeEnergy(2);
									players[i]->addEnergyCubes(2);
									cout << players[i]->getName() << " stole 2 Energy from " << player.getName() << endl;
								}
								else if (player.getEnergyCubes() == 1) {
									player.removeEnergy(1);
									players[i]->addEnergyCubes(1);
									cout << players[i]->getName() << " stole 1 Energy from " << player.getName() << endl;
								}
								else {
									player.removeEnergy(93); //Just to trigger the not enough funds message, passing a high value
								}
							}
						}

						//Check if attacked player has Phoenix Blood card
						for (int j = 0; j < cardsAttacked.size(); j++) {
							if (cardsAttacked[j]->getName() == "Phoenix Blood") {
								cardsAttacked[j]->useCard();
								players[i]->addEnergyCubes(1);
							}

						}


						cout << players[i]->getName() << " just lost " << damageDealt << " health by being attacked." << endl;
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
						int damageDealt = effect.size();
						vector<EffectCard*> cards = player.getCards();

						//Check if attacked player has Shadow Double card, then remove 2 energy from the attacker
						for (int j = 0; j < cards.size(); j++) {
							if (cards[j]->getName() == "Shadow Double") {
								cards[j]->useCard();
								damageDealt += effect.size();
							}

						}

						//Check if attacked player has Tesla Antenna card, then remove 2 energy from the attacker
						for (int j = 0; j < cards.size(); j++) {
							//If player has the card and less health than opponent, deal 1 extra damage
							if (cards[j]->getName() == "Tesla Antennae" &&(player.getHealth() < players[i]->getHealth())) {
								cards[j]->useCard();
								damageDealt++;
							}

						}



						players[i]->removeHealth(damageDealt);
						vector<EffectCard*> cardsAttacked = players[i]->getCards();
						//Check if attacked player has Drain card, then remove 2 energy from the attacker
						for (int j = 0; j < cardsAttacked.size(); j++) {
							if (cardsAttacked[j]->getName() == "Drain") {
								cardsAttacked[j]->useCard();
								if (player.getEnergyCubes() >= 2) {
									player.removeEnergy(2);
									players[i]->addEnergyCubes(2);
									cout << players[i]->getName() << " stole 2 Energy from " << player.getName() << endl;
								}
								else if (player.getEnergyCubes() == 1) {
									player.removeEnergy(1);
									players[i]->addEnergyCubes(1);
									cout << players[i]->getName() << " stole 1 Energy from " << player.getName() << endl;
								}
								else {
									player.removeEnergy(93); //Just to trigger the not enough funds message, passing a high value
								}
							}
						}
						//Check if attacked player has Phoenix Blood card
						for (int j = 0; j < cardsAttacked.size(); j++) {
							if (cardsAttacked[j]->getName() == "Phoenix Blood") {
								cardsAttacked[j]->useCard();
								players[i]->addEnergyCubes(1);
							}

						}


						cout << players[i]->getName() << " just lost " << damageDealt << " health by being attacked." << endl;
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

	//This is to convert the user input to a string of int when rerolling dices
	vector<int> stringToVectorInt(string reRolls)
	{
		stringstream iss(reRolls);
		int number;
		vector<int> myNumbers;


		while (iss >> number)
			myNumbers.push_back(number);
		return myNumbers;
	}

};