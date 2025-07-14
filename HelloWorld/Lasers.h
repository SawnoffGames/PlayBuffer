#pragma once

#include "GameState.h"

class Lasers
{
public:
	Lasers(GameState* state);
	void Update();
	void Draw();

private:
	GameState* gameState;
};