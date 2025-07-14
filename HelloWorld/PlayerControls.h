#pragma once

#include "GameState.h"

class PlayerControls
{
public:
	PlayerControls(GameState* state);
	void HandlePlayerControls();

private:
	GameState* gameState;
};
