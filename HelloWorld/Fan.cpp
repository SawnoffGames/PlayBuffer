#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Fan.h"

#include "Play.h"
#include "GameObjectType.h"

Fan::Fan()
{
	id_fan = Play::CreateGameObject(TYPE_FAN, { 1140, 503 }, 0, "fan");
	Play::GetGameObject(id_fan).velocity = { 0, -3 };
	Play::GetGameObject(id_fan).animSpeed = 1.0f;
}

void Fan::Update()
{
	Play::GameObject& obj_fan = Play::GetGameObject(id_fan);

	if (Play::RandomRoll(50) == 50)
	{
		int id = Play::CreateGameObject(TYPE_TOOL, obj_fan.pos, 50, "driver");

		Play::GameObject& obj_tool = Play::GetGameObject(id);

		obj_tool.velocity = Play::Point2f(-8, Play::RandomRollRange(-1, 1) * 6);

		if (Play::RandomRoll(2) == 1)
		{
			Play::SetSprite(obj_tool, "spanner", 0);
			obj_tool.radius = 100;
			obj_tool.velocity.x = -4;
			obj_tool.rotSpeed = 0.1f;
		}

		Play::PlayAudio("tool");
	}

	if (Play::RandomRoll(150) == 1)
	{
		int id = Play::CreateGameObject(TYPE_COIN, obj_fan.pos, 40, "coin");

		Play::GameObject& obj_coin = Play::GetGameObject(id);

		obj_coin.velocity = { -3,0 };
		obj_coin.rotSpeed = 0.1f;
	}

	Play::UpdateGameObject(obj_fan);

	if (Play::IsLeavingDisplayArea(obj_fan))
	{
		obj_fan.pos = obj_fan.oldPos;
		obj_fan.velocity.y *= -1;
	}
}

void Fan::Draw()
{
	Play::GameObject& obj_fan = Play::GetGameObject(id_fan);

	Play::DrawObject(obj_fan);
}