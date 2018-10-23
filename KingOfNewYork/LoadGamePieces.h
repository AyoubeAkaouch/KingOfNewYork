#pragma once
#include <vector>
#include <map>
#include "Token.h"
#include "Monster.h"
#include "EffectCard.h"
#include "EffectCardDeck.h"
#include "BuildingTiles.h"
#include "BuildingTilesDeck.h"

using namespace std;

class LoadGamePieces
{
public:
	LoadGamePieces();
	~LoadGamePieces();
	static void LoadAllPieces(vector<Monster> &monsters, BuildingTilesDeck & bDeck, EffectCardDeck &eDeck, map<string, vector<Token>> &tokens);
};

