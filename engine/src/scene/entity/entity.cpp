
#include "entity.h"


namespace Bubble
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: EntityHandle(handle),
		  m_Scene(scene)
	{}
}