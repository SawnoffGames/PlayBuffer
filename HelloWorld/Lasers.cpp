#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Lasers.h"

#include "Play.h"
#include "GameObjectType.h"
#include "GameState.h"

Lasers::Lasers(GameState* state) : gameState(state)
{
}

void Lasers::Update()
{
	std::vector<int> vLasers = Play::CollectGameObjectIDsByType(TYPE_LASER);
	std::vector<int> vTools = Play::CollectGameObjectIDsByType(TYPE_TOOL);
	std::vector<int> vCoins = Play::CollectGameObjectIDsByType(TYPE_COIN);

	for (int id_laser : vLasers)
	{
		Play::GameObject& obj_laser = Play::GetGameObject(id_laser);

		bool hasCollided = false;

		for (int id_tool : vTools)
		{
			Play::GameObject& obj_tool = Play::GetGameObject(id_tool);

			if (Play::IsColliding(obj_laser, obj_tool))
			{
				hasCollided = true;
				obj_tool.type = TYPE_DESTROYED;
				gameState->score += 100;
			}
		}

		for (int id_coin : vCoins)
		{
			Play::GameObject& obj_coin = Play::GetGameObject(id_coin);

			if (Play::IsColliding(obj_laser, obj_coin))
			{
				hasCollided = true;
				obj_coin.type = TYPE_DESTROYED;
				Play::PlayAudio("error");
				gameState->score -= 300;
			}
		}

		gameState->score = std::max(gameState->score, 0);

		Play::UpdateGameObject(obj_laser);

		if (!Play::IsVisible(obj_laser) || hasCollided)
		{
			Play::DestroyGameObject(id_laser);
		}
	}
}

void Lasers::Draw()
{
	std::vector<int> vLasers = Play::CollectGameObjectIDsByType(TYPE_LASER);

	for (int id_laser : vLasers)
	{
		Play::GameObject& obj_laser = Play::GetGameObject(id_laser);

		Play::DrawObject(obj_laser);
	}
}