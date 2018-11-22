#pragma once

#include "Player.h"
#include "GameMap.h"
#include "EffectCard.h"
#include "EffectCardDeck.h"
#include "Region.h"

class Player;
class GameMap;

class StrategyPlayerInterface {
public:
	virtual bool move(Player & player, GameMap & gameMap, bool gotAttacked)  = 0;
	virtual vector<string> resolveDices(Player & player, GameMap& gameMap, vector<Player*> & players) = 0;
	virtual void diceRoll(Player & player, bool extraDices) = 0;
	virtual void buyCards(Player & player, vector<EffectCard*>& buyableCards, EffectCardDeck & effectCards) = 0;
};