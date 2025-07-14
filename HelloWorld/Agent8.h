#pragma once

#include "GameState.h"
#include "PlayerControls.h"

class Agent8
{
public:
	Agent8(GameState* state, PlayerControls* playerControls);
	void Update();
	void Draw();

private:
	GameState* gameState;
	PlayerControls* playerControls;
};