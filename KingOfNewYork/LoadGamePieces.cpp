#include "LoadGamePieces.h"



LoadGamePieces::LoadGamePieces()
{
}


LoadGamePieces::~LoadGamePieces()
{
}

void LoadGamePieces::LoadAllPieces(vector<Monster>& monsters, BuildingTilesDeck & bDeck, EffectCardDeck & eDeck, map<string,vector<Token>>& tokens, ConcreteCardObserver* cardObserver)
{
	//Setting up the Cards first (PlaceHolders)
	vector<EffectCard*> cardObjects;
	std::map<string, int> effectPlaceholder;
	effectPlaceholder["victory"] = 2;//Gives 2 victory points

	

	//Creating the tower titan card
	EffectCard* card = new EffectCard(10,"keep", "Towering Titan" , "Add 2 ATTACK to your result.",effectPlaceholder);
	card->registerOb(cardObserver);
	cardObjects.push_back(card);

	//Creating the stomp card
	card = new EffectCard(4, "keep", "Stomp", "Add 1 DESTRUCTION to your result.", effectPlaceholder);
	card->registerOb(cardObserver);
	cardObjects.push_back(card);

	//Creating the King Of Queens card
	card = new EffectCard(5, "keep", "King of Queens", "Gain 1 ENERGY_POINT and heal 1 damage when you start your turn in Queens.", effectPlaceholder);
	card->registerOb(cardObserver);
	cardObjects.push_back(card);

	//Creating the Super Speed card
	card = new EffectCard(4, "keep", "Super Speed", "You can have an extra move before rolling your dice.", effectPlaceholder);
	card->registerOb(cardObserver);
	cardObjects.push_back(card);
	
	//Creating the drain card
	card = new EffectCard(4, "keep", "Drain", "Take 2 ENERGY_POINT from Monsters that attack you.", effectPlaceholder);
	card->registerOb(cardObserver);
	cardObjects.push_back(card);


	eDeck.setDeck(cardObjects);
	eDeck.shuffle(); //Be sure the returned deck is shuffled

	//Setting up building tiles (Real Tiles)
	vector<BuildingTiles> buildingTiles;
	//22 building 1 health
	for (int i = 0; i < 22;i++) {
		buildingTiles.push_back(BuildingTiles("Building1"));
	}
	//8 building with 2 health
	for (int i = 0; i < 8;i++) {
		buildingTiles.push_back(BuildingTiles("Building2"));
	}
	for (int i = 0; i < 3; i++) {
		buildingTiles.push_back(BuildingTiles("Building3"));
	}
	for (int i = 0; i < 3; i++) {
		buildingTiles.push_back(BuildingTiles("Hospital2"));
	}
	for (int i = 0; i < 3; i++) {
		buildingTiles.push_back(BuildingTiles("Hospital3"));
	}
	for (int i = 0; i < 3; i++) {
		buildingTiles.push_back(BuildingTiles("Plant2"));
	}
	for (int i = 0; i < 3; i++) {
		buildingTiles.push_back(BuildingTiles("Plant3"));
	}

	bDeck.setDeck(buildingTiles);
	bDeck.shuffle();//Making sure the building tiles are shuffled 

	//Creating all the monsters
	monsters.push_back(Monster("Captain Fish"));
	monsters.push_back(Monster("Mantis"));
	monsters.push_back(Monster("Rob"));
	monsters.push_back(Monster("Kong"));
	monsters.push_back(Monster("Drakonis"));
	monsters.push_back(Monster("Sheriff"));

	//Creating all the needed tokens
	vector<Token> web, jynx, souvenir, carapace;

	for (int i = 0; i < 13 ; i++) {
		web.push_back(Token("Web"));
	}
	for (int i = 0; i < 13 ; i++) {
		jynx.push_back(Token("Jynx"));
	}
	for (int i = 0; i < 5 ; i++) {
		souvenir.push_back(Token("Souvenir"));
	}
	for (int i = 0; i < 15 ; i++) {
		carapace.push_back(Token("Carapace"));
	}
	tokens["Web"] = web;
	tokens["Jynx"] = jynx;
	tokens["Souvenir"] = souvenir;
	tokens["Carapace"] = carapace;
	
}
