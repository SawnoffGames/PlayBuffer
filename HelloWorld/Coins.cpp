#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Coins.h"

#include "Play.h"
#include "GameObjectType.h"
#include "GameState.h"

Coins::Coins(GameState* state) : gameState(state)
{
}

void Coins::Update()
{
	Play::GameObject& obj_agent8 = Play::GetGameObjectByType(TYPE_AGENT8);
	std::vector<int> vCoins = Play::CollectGameObjectIDsByType(TYPE_COIN);

	for (int id_coin : vCoins)
	{
		Play::GameObject& obj_coin = Play::GetGameObject(id_coin);
		bool hasCollided = false;

		if (Play::IsColliding(obj_coin, obj_agent8))
		{
			for (float rad{ 0.25f }; rad < 2.0f; rad += 0.5f)
			{
				int id = Play::CreateGameObject(TYPE_STAR, obj_agent8.pos, 0, "star");

				Play::GameObject& obj_star = Play::GetGameObject(id);

				obj_star.rotSpeed = 0.1f;
				obj_star.acceleration = { 0.0f, -0.5f };

				Play::SetGameObjectDirection(obj_star, 16, rad * Play::PLAY_PI);
			}

			hasCollided = true;
			gameState->score += 500;
			Play::PlayAudio("collect");
		}

		Play::UpdateGameObject(obj_coin);

		if (!Play::IsVisible(obj_coin) || hasCollided)
		{
			Play::DestroyGameObject(id_coin);
		}
	}
}

void Coins::Draw()
{
	std::vector<int> vCoins = Play::CollectGameObjectIDsByType(TYPE_COIN);

	for (int id_coin : vCoins)
	{
		Play::GameObject& obj_coin = Play::GetGameObject(id_coin);

		Play::DrawObjectRotated(obj_coin);
	}
}