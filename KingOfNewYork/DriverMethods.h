#pragma once
#include "Player.h"
#include "GameMap.h"
#include "Region.h"
#include "EffectCardDeck.h"
#include "BuildingTilesDeck.h"
#include "StrategyPlayerInterface.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

 int firstPlayer(vector<Player*>& players);
 void settingRegions(GameMap& gameMap, vector<Player*>& players, int currentTurn);
 void setPlayers(vector<Player*>& players, vector<Monster>& monsters,ObserverInterface* observer);
 void gameLoop(vector<Player*>& players, GameMap& gameMap, EffectCardDeck& effectCards, BuildingTilesDeck& tilesDeck, map<string, vector<Token>>& tokens,int firstToPlay);
 bool gameEnded(vector<Player*>& players, GameMap& gameMap);// In this one we remove all players that are at 0 health and check if winning condition achieved!