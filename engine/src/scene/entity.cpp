
#include "entity.h"

namespace Bubble
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: mEntityHandle(handle),
		  mScene(scene)
	{}
}