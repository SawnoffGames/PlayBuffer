#define PLAY_USING_GAMEOBJECT_MANAGER

#include <vector>

#include "Play.h"
#include "GameObjectType.h"
#include "DestroyObjects.h"

void DestroyObjects::UpdateDestroyed()
{
	std::vector<int> vDead = Play::CollectGameObjectIDsByType(TYPE_DESTROYED);

	for (int id_dead : vDead)
	{
		Play::GameObject& obj_dead = Play::GetGameObject(id_dead);

		obj_dead.animSpeed = 0.2f;

		Play::UpdateGameObject(obj_dead);

		if (obj_dead.frame % 2)
		{
			Play::DrawObjectRotated(obj_dead, (10 - obj_dead.frame) / 10.0f);
		}

		if (!Play::IsVisible(obj_dead) || obj_dead.frame >= 10)
		{
			Play::DestroyGameObject(id_dead);
		}
	}
}
