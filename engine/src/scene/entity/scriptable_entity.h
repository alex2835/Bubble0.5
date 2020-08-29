#pragma once

#include "entity.h"


namespace Bubble
{
	struct ScriptableEntity
	{
		Entity m_Entity;
		friend class Scene;

		virtual ~ScriptableEntity() {}

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
	
	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(DeltaTime dt) {}
	};
}