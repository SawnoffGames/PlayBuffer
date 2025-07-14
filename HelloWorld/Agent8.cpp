#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Agent8.h"

#include "Play.h"
#include "Constants.h"
#include "GameObjectType.h"
#include "GameState.h"
#include "PlayerControls.h"

Agent8::Agent8(GameState* state, PlayerControls* playerControls) : gameState(state), playerControls(playerControls)
{
}

void Agent8::Update()
{
	Play::GameObject& obj_agent8 = Play::GetGameObjectByType(TYPE_AGENT8);

	switch (gameState->agent8State)
	{
		case STATE_APPEAR:
			obj_agent8.velocity = { 0, -12 };
			obj_agent8.acceleration = { 0, -0.5f };

			Play::SetSprite(obj_agent8, "agent8_fall", 0);

			obj_agent8.rotation = 0;

			if (obj_agent8.pos.y <= DISPLAY_HEIGHT * 0.66f)
			{
				gameState->agent8State = STATE_PLAY;
			}

			break;
		case STATE_HALT:
			obj_agent8.velocity *= 0.9f;

			if (Play::IsAnimationComplete(obj_agent8))
			{
				gameState->agent8State = STATE_PLAY;
			}

			break;
		case STATE_PLAY:
			playerControls->HandlePlayerControls();

			break;
		case STATE_DEAD:
			obj_agent8.acceleration = { 0.3f, 0.5f };
			obj_agent8.rotation += 0.25f;

			if (Play::KeyPressed(Play::KEY_SPACE) == true)
			{
				gameState->agent8State = STATE_APPEAR;

				obj_agent8.pos = { 115, 600 };
				obj_agent8.velocity = { 0, 0 };
				obj_agent8.frame = 0;

				Play::StartAudioLoop("music");
				gameState->score = 0;

				for (int id_obj : Play::CollectGameObjectIDsByType(TYPE_TOOL))
				{
					Play::GetGameObject(id_obj).type == TYPE_DESTROYED;
				}
			}
			break;
	}

	Play::UpdateGameObject(obj_agent8);

	if (Play::IsLeavingDisplayArea(obj_agent8) && gameState->agent8State != STATE_DEAD)
	{
		obj_agent8.pos = obj_agent8.oldPos;
	}

	Play::DrawLine({ obj_agent8.pos.x, 720 }, obj_agent8.pos, Play::cWhite);
	Play::DrawObjectRotated(obj_agent8);
}

void Agent8::Draw()
{
	Play::GameObject& obj_agent8 = Play::GetGameObjectByType(TYPE_AGENT8);

	Play::DrawLine({ obj_agent8.pos.x, 720 }, obj_agent8.pos, Play::cWhite);
	Play::DrawObjectRotated(obj_agent8);
}
