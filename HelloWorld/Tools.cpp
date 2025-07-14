#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Tools.h"

#include "Play.h"
#include "GameObjectType.h"
#include "GameState.h"

Tools::Tools(GameState* state) : gameState(state)
{
}

void Tools::Update()
{
	Play::GameObject& obj_agent8 = Play::GetGameObjectByType(TYPE_AGENT8);
	std::vector<int> vTools = Play::CollectGameObjectIDsByType(TYPE_TOOL);

	for (int id : vTools)
	{
		Play::GameObject& obj_tool = Play::GetGameObject(id);

		if (gameState->agent8State != STATE_DEAD && Play::IsColliding(obj_tool, obj_agent8))
		{
			Play::StopAudio("music");
			Play::PlayAudio("die");

			gameState->agent8State = STATE_DEAD;
		}

		Play::UpdateGameObject(obj_tool);

		if (Play::IsLeavingDisplayArea(obj_tool, Play::VERTICAL))
		{
			obj_tool.pos = obj_tool.oldPos;
			obj_tool.velocity.y *= -1;
		}

		if (!Play::IsVisible(obj_tool))
		{
			Play::DestroyGameObject(id);
		}
	}
}

void Tools::Draw()
{
	std::vector<int> vTools = Play::CollectGameObjectIDsByType(TYPE_TOOL);

	for (int id : vTools)
	{
		Play::GameObject& obj_tool = Play::GetGameObject(id);

		Play::DrawObjectRotated(obj_tool);
	}
}