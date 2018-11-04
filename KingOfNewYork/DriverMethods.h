#pragma once
#include "Player.h"
#include "GameMap.h"
#include "EffectCardDeck.h"
#include "BuildingTilesDeck.h"
using namespace std;

 int firstPlayer(vector<Player> players);
 void settingRegions(GameMap& gameMap, vector<Player>& players, int currentTurn);
 void setPlayers(vector<Player>& players, vector<Monster>& monsters);
 void gameLoop(vector<Player>& players, GameMap& gameMap, EffectCardDeck& effectCards, BuildingTilesDeck& tilesDeck, map<string, vector<Token>>& tokens,int firstToPlay);
 void diceRoll(Player& player);
 void resolveDices(Player& player);
 void move(Player& player, GameMap& gameMap);
 void buyCards(Player& player,vector<EffectCard>& buyableCards,EffectCardDeck& effectCards);
 bool gameEnded();