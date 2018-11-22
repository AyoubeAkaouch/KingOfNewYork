#include "LoadGamePieces.h"



LoadGamePieces::LoadGamePieces()
{
}


LoadGamePieces::~LoadGamePieces()
{
}

void LoadGamePieces::LoadAllPieces(vector<Monster>& monsters, BuildingTilesDeck & bDeck, EffectCardDeck & eDeck, map<string,vector<Token>>& tokens)
{
	//Setting up the Cards first (PlaceHolders)
	vector<EffectCard*> cardObjects;
	std::map<string, int> effectPlaceholder;
	effectPlaceholder["victory"] = 2;//Gives 2 victory points

	for (int i = 0; i < 64; i++)
	{
		string cardName = "Card " + to_string(i);
		cardObjects.push_back((new EffectCard(i, cardName, "PlaceHolder definition for the moment", effectPlaceholder)));
	}

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
