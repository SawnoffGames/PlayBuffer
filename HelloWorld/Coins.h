#pragma once
#include "GameState.h"

class Coins
{
public:
	Coins(GameState* state);
	void Update();
	void Draw();

private:
	GameState* gameState;
};
