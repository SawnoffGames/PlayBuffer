#define PLAY_USING_GAMEOBJECT_MANAGER

#include "PlayerControls.h"

#include "Play.h"
#include "GameObjectType.h"
#include "GameState.h"

PlayerControls::PlayerControls(GameState* state) : gameState(state)
{
}

void PlayerControls::HandlePlayerControls()
{
	Play::GameObject& obj_agent8 = Play::GetGameObjectByType(TYPE_AGENT8);

	if (Play::KeyDown(Play::KEY_UP))
	{
		obj_agent8.velocity = { 0, 4 };
		 
		Play::SetSprite(obj_agent8, "agent8_climb", 0.25f);
	}
	else if (Play::KeyDown(Play::KEY_DOWN))
	{
		obj_agent8.velocity = { 0, -1 };

		Play::SetSprite(obj_agent8, "agent8_fall", 0);
	}
	else
	{
		if (obj_agent8.velocity.y < -5)
		{
			gameState->agent8State = STATE_HALT;

			Play::SetSprite(obj_agent8, "agent8_halt", 0.333f);

			obj_agent8.acceleration = { 0,0 };
		}
		else
		{
			Play::SetSprite(obj_agent8, "agent8_hang", 0.02f);

			obj_agent8.velocity *= 0.5f;
			obj_agent8.acceleration = { 0,0 };
		}
	}

	if (Play::KeyPressed(Play::KEY_SPACE))
	{
		Play::Vector2D firePos = obj_agent8.pos + Play::Vector2D(155, 75);

		int id = Play::CreateGameObject(TYPE_LASER, firePos, 30, "laser");

		Play::GetGameObject(id).velocity = { 32,0 };
		Play::PlayAudio("shoot");
	}

	Play::UpdateGameObject(obj_agent8);

	if (Play::IsLeavingDisplayArea(obj_agent8))
	{
		obj_agent8.pos = obj_agent8.oldPos;
	}

	Play::DrawLine({ obj_agent8.pos.x, 720 }, obj_agent8.pos, Play::cWhite);
	Play::DrawObjectRotated(obj_agent8);
}
