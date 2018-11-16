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
	virtual void move(Player & player, GameMap & gameMap, bool gotAttacked) = 0;
	virtual void resolveDices(Player & player, GameMap& gameMap, vector<Player> & players) = 0;
	virtual void diceRoll(Player & player, bool extraDices) = 0;
	virtual void buyCards(Player & player, vector<EffectCard>& buyableCards, EffectCardDeck & effectCards) = 0;
};