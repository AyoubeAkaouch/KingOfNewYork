#include "DriverMethods.h"
#include "AggressivePlayerStrategy.cpp"
#include "BalancedPlayerStrategy.cpp"
#include "HumanPlayerStrategy.cpp"


using namespace std;

int firstPlayer(vector<Player*>& players) {
	int bestPlayerRollPosition=0, currentBestRoll=0, numberOfAttacks=0;
	vector<int> equalTopRolls; // Used to deal with equal rolls

	cout << "~~~~~~~~~~~We are now determining who goes first!~~~~~~~~~~~" << endl << endl;

	for (int i = 0; i < players.size(); i++) {
		cout << players[i]->getName() << " press Enter to roll your dices!" << endl;
		map<int, string > current = players[i]->RollDicesExtra();
		cout << players[i]->getDices() << endl << endl;
		for (int j = 0; j < current.size();j++) {
			
			if (current[j] == "Attack") {
				numberOfAttacks++;
			}
		}
		if (numberOfAttacks == currentBestRoll) {
			equalTopRolls.push_back(i);
		}
		else if (numberOfAttacks > currentBestRoll) {
			currentBestRoll = numberOfAttacks;
			bestPlayerRollPosition = i;

			//Clearing out this vector since no need to reroll
			equalTopRolls.clear();
			equalTopRolls.push_back(i);
		}
		numberOfAttacks = 0; // Reseting our counter
	}

	while (equalTopRolls.size() > 1)
	{
		cout << "\n~~~~Some players rolled the same number of Attacks and are tied for first turn!" << endl;
		cout << "Rerolls for players that are tied!" << endl << endl;
		vector<int> rerolls = equalTopRolls;
		//Restarting the values
		bestPlayerRollPosition = 0, currentBestRoll = 0, numberOfAttacks = 0;
		//Clearing out the equals!
		equalTopRolls.clear();

		for (int i = 0; i < rerolls.size(); i++) {
			cout << players[rerolls[i]]->getName() << " press Enter to roll your dices!" << endl;
			//cin.get();
			map<int, string > current = players[rerolls[i]]->RollDicesExtra();
			cout << players[rerolls[i]]->getDices() << endl;
			for (int j = 0; j < current.size(); j++) {

				if (current[j] == "Attack") {
					numberOfAttacks++;
				}
			}
			
			if (numberOfAttacks == currentBestRoll) {
				equalTopRolls.push_back(rerolls[i]);
			}
			else if (numberOfAttacks > currentBestRoll) {
				currentBestRoll = numberOfAttacks;
				bestPlayerRollPosition = rerolls[i];

				//Clearing out this vector since no need to reroll
				equalTopRolls.clear();
				equalTopRolls.push_back(rerolls[i]);
			}
			numberOfAttacks = 0; // Reseting our counter
		}
	}
	cout << players[bestPlayerRollPosition]->getName() << " starts! Then the others play clockwise" << endl;

	return bestPlayerRollPosition;

}

void settingRegions(GameMap& gameMap, vector<Player*>& players, int currentTurn) {
	cout << "~~~~~~~~~~~~~We are now setting up the pieces on the board!~~~~~~~~~~~~~" << endl;
	cout << "--------------------------------MAP--------------------------------"<< endl << endl;
	cout << gameMap;

	vector<Region> availableRegion = gameMap.getAllRegions();
	int selectedRegion;
	bool isSet;

	//Showing the possible regions for him to go
	cout << "All the regions in this map: ";
	for (int i = 0; i < availableRegion.size();i++) {
		
		cout << i << ") " << availableRegion[i].getName() << " ";	
		
	}
	cout << endl;

	
	for (int i = 0; i < players.size() ; i++ ) {
		isSet = false;
		cout << players[(i + currentTurn) % players.size()]->getName() << " which region do you want to start in (Choose by index)?"<<endl;
		while (!isSet) {
			cin >> selectedRegion;
			if (availableRegion[selectedRegion].getName() == "Manhattan") {
				cout << "A player can't select Manhattan as his staring region, Please select another one!" << endl;
			}
			else {
				isSet = gameMap.setOwnerRegion(players[(i + currentTurn) % players.size()]->getName(), availableRegion[selectedRegion]);
				if (!isSet) {
					cout << "Select another region please." << endl;
				}
			}
		}
		players[(i + currentTurn) % players.size()]->setRegion(availableRegion[selectedRegion]);
	}
}

void setPlayers(vector<Player*>& players, vector<Monster>& monsters,StrategyPlayerInterface* strategy)
{
	//Setup the number of players and associate them to a monster card
	int numberOfPlayers;
	do {
		cout << "How many players will be playing this game? (Has to be between 2 or 6 players)" << endl;
		cin >> numberOfPlayers;
	} while (numberOfPlayers < 2 || numberOfPlayers > 6);


	cout << "Please select your player in the clockwise order you are sitting." << endl;
	for (int i = 1; i <= numberOfPlayers; i++) {
		int x;
		cout << "Player " << i << " please choose from this list which monster you want to pick.(Choose by index)" << endl;
		cout << "{ ";
		for (int j = 0; j < monsters.size(); j++) {
			cout << "\"" << monsters[j].getName() << "\" ";
		}
		cout << " }" << endl;
		cin >> x;
		if (i%3==0) {
			players.push_back(new Player(monsters[x], new AggressivePlayerStrategy()));
			monsters.erase(monsters.begin() + x);
		}
		else if(i%3==1){
			players.push_back(new Player(monsters[x], new BalancedPlayerStrategy()));
			monsters.erase(monsters.begin() + x);
		}
		else {
			players.push_back(new Player(monsters[x], new HumanPlayerStrategy()));
			monsters.erase(monsters.begin() + x);
		}
	}
}


void gameLoop(vector<Player*>& players, GameMap & gameMap, EffectCardDeck & effectCards, BuildingTilesDeck & tilesDeck, map<string, vector<Token>>& tokens, int firstToPlay)
{
	vector<EffectCard> buyableCards; // This will be a smaller deck of 3 cards that the player can purchase
	effectCards.shuffle(); //Making sure all cards are shuffled before drawing the top 3
	string stop = "x";

	for (int i = 0; i < 3; i++) {
		buyableCards.push_back(effectCards.draw());
	}
	
	int turnOf = firstToPlay;
	players[turnOf]->addEnergyCubes(50); //To test the buying card feature!
	while (!gameEnded(players,gameMap) && stop == "x") //This method will check if game ended yet (20 victory points or only 1 player left)
	{
		//If player doesn't have any health he can't play anymore
		if (players[turnOf]->getHealth()>0) {
			cout << endl << "It is now " << players[turnOf]->getName() << "\'s turn." << endl;

			players[turnOf]->diceRoll(*players[turnOf], false);//Up to 3times, rerolls will be handled inside this method
			cout << endl;
			players[turnOf]->resolveDices(*players[turnOf], gameMap, players);//Mandatory
			cout << endl;
			players[turnOf]->move(*players[turnOf], gameMap, false); //Method will check if player wants to move or not, will also check if manhattan is empty it will move him there automatically
			cout << endl;
			players[turnOf]->buyCards(*players[turnOf], buyableCards, effectCards); //Will first prompt the player to ask if he wants to buy card, then will proceed.
			cout << endl;
		}
		
		turnOf = (turnOf + 1) % players.size();//Setting up the nexts persons turn
		cout << "Press x to continue, anything else to stop" << endl;
		cin >> stop;
	}
}

void diceRoll(Player & player,bool extraDices)
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


	cout << "Here is the first roll :\n" << player.getDices();
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
			cout << "\nHere are your current dices:\n" << player.getDices();
		}
		else
		{
			break;
		}
	}

}

void resolveDices(Player & player, GameMap& gameMap, vector<Player*> & players)
{
	string toResolve;
	vector<string> sameToResolve;
	vector<string> resolved; // Since we are getting a pointer we can't erase from map what has already been resolve, it wil change dice object.
	map<int, string> currentDices = player.getCurrentValues();
	int dicesResolved = 0;
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
		applyDiceEffect(sameToResolve,player,gameMap,players); //applying on a vector to apply all effect at the same time.
		sameToResolve.clear(); // So that we can do this again with next effect we wish to apply.
		resolved.push_back(toResolve);
	}
}

void move(Player & player, GameMap & gameMap,bool gotAttacked)
{
	vector<Region> availableRegion = gameMap.getAllRegions();
	int indexManhattan;
	char changeRegion;
	int selectedRegion;
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
	}
	//If already in manhattan, move player one level upper
	else if (player.getRegion().getName() == "Manhattan" && !gotAttacked) {
		cout << "You are currently in Manhattan, you can't change boroughs but you are moving one space up inside of Manhattan!" << endl;
	}
	//If in Manhattan and got attacked offer the player to move somewhere else.
	else if (player.getRegion().getName() == "Manhattan" && gotAttacked) {
		Region currentRegionName = player.getRegion();
		cout << "Oh no! Another player attacked you :( Would you like to move to a different borough outside of Manhattan?(y/n)" << endl;
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
			gameMap.removeOwner(player.getName(), player.getRegion());// Removing player from his current Region
			player.setRegion(availableRegion[selectedRegion]);
			cout << player.getName() << " was moved to " << availableRegion[selectedRegion].getName() << endl;
			cout << "Manhattan is now empty watch out!" << endl;

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
			cout << "THE REGION INSIDE PLAYER OBJECT "<<player.getRegion().getName();
			gameMap.removeOwner(player.getName(), player.getRegion());// Removing player from his current Region
			player.setRegion(availableRegion[selectedRegion]);
			cout << player.getName() << " was moved to " << availableRegion[selectedRegion].getName() << endl;
		}
	}



}

void buyCards(Player & player, vector<EffectCard>& buyableCards, EffectCardDeck & effectCards)
{
	char input;
	int input2;
	bool done = false;
	cout << "Would you like to buy a card? (y/n)" << endl;
	cin >> input;
	if (input == 'y') {
		cout << "Here are the 3 cards that you can buy:" << endl;
		for (int i = 0; i < buyableCards.size(); i++) {
			cout << i << ") " << buyableCards[i] << endl;
		}
		while (!done) {
			cout << "Your current balance is: " << player.getEnergyCubes() << endl;
			cout << "Choose card you wish to buy by index, press 3 to pay 2 energies and get 3 new cards, press 4 to quit buying." << endl;
			cin >> input2;
			if (input2 >= 0 && input2 <= 2) {
				done = player.buyCards(buyableCards[input2]);
				if (done) {
					buyableCards.erase(buyableCards.begin() + input2);
					buyableCards.push_back(effectCards.draw());
					cout << "The card you bought got replaced by this one: " << endl;
					cout << buyableCards[2] << endl;
				}
			}
			else if (input2 == 3) {
				if (player.removeEnergy(2)) {
					buyableCards.clear();
					for (int i = 0; i < 3; i++) {
						buyableCards.push_back(effectCards.draw());
					}
					cout << "Here are the 3 cards that you can buy:" << endl;
					for (int i = 0; i < buyableCards.size(); i++) {
						cout << i << ") " << buyableCards[i] << endl;
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

vector<int> stringToVectorInt(string reRolls)
{
	stringstream iss(reRolls);
	int number;
	vector<int> myNumbers;


	while (iss >> number)
		myNumbers.push_back(number);
	return myNumbers;
}

bool gameEnded(vector<Player*>& players, GameMap& gameMap)
{
	static vector<int> deletedPlayers;
	for (int i = 0; i < players.size() ; i++) {
		//Deleting player from the game! No more turns for him. Removing him from gameMap
		if (players[i]->getHealth()<=0) {
			bool alreadyDeleted = false;
			for (int j = 0; j < deletedPlayers.size(); j++) {
				if (deletedPlayers[j] == i) {
					alreadyDeleted = true;
					break;
				}
				
			}
			if (!alreadyDeleted) {
				cout << players[i]->getName() << " you have lost and been removed from the game Map." << endl;
				gameMap.removeOwner(players[i]->getName(), players[i]->getRegion());// Removing player from his current Region
				deletedPlayers.push_back(i);
			}
			
		}

	}
	//Checks if only one player left, declare winner and return true
	if (deletedPlayers.size() + 1 == players.size()) {
		for (int i = 0; i < players.size(); i++) {
			if (players[i]->getHealth() > 0)
			{
				cout << players[i]->getName() << " won!! He is the last monster standing." << endl;
			}
		}
		return true;
	}

	for (int i = 0; i < players.size(); i++) {
		if (players[i]->getVictoryPoints() >= 20) {
			cout << players[i]->getName() << " won!!He is the first monster to get 20 victory points!!" << endl;
			return true;
		}
	}

	return false;
}

void applyDiceEffect(vector<string> effect,Player& player,GameMap& gameMap, vector<Player*> & players) {
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
			if (effect.size() < 3){
				cout << "Sorry but these celebrity dices do not have any effects you don't have enough or you dont have the superstar card!" << endl;
			}
			//Player aquires the superstar card and gets 1 victory points + 1 per extra celebirty;
			else {
				gameMap.setOwnerSuperStar(player,players);
				player.addPoints(effect.size()-2);
				cout << player.getName() << " just gained " << effect.size() - 2  << " victory points and gained the superstar card." << endl;
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
					move(*players[i],gameMap,true);
				}
			}
			//If no one in manhattan the attack dices had no effect
			if (noOneInManhattan) {
				cout << "No one was in Manhattan! The Attack dices did not impact anyone!" << endl;
			}
		}
	}
	else if (effect[0]=="Energy") {
		player.addEnergyCubes(effect.size());
		cout << player.getName() << " just gained " << effect.size() << " energy cubes." << endl;
	}
	else if (effect[0]=="Heal") {
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

