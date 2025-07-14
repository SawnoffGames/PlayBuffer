#pragma once

#include "Agent8State.h"

struct GameState
{
	float timer = 0;
	int spriteId = 0;
	int score = 0;
	Agent8State agent8State{ STATE_APPEAR };
};
