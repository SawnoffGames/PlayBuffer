#pragma once

#include "GameState.h"

class Tools
{
public:
	Tools(GameState* state);
	void Update();
	void Draw();

private:
	GameState* gameState;
};