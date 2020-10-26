#pragma once

#include "scene.h"


namespace Bubble
{
	class Entity
	{
		entt::entity EntityHandle = entt::null;
		Scene* m_Scene = nullptr;

	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		
		template<typename T, typename... Args>
		T& EmplaceComponent(Args&&... args) const
		{
			BUBBLE_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return m_Scene->Registry.emplace<T>(EntityHandle, std::forward<Args>(args)...);
		}


		template<typename T, typename... Args>
		const Entity& AddComponent(Args&&... args) const
		{
			BUBBLE_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			m_Scene->Registry.emplace<T>(EntityHandle, std::forward<Args>(args)...);
			return *this;
		}


		template<typename... Args>
		auto GetComponent() const
		{
			return m_Scene->Registry.get<Args...>(EntityHandle);
		}


		bool Valid()
		{
			return m_Scene && m_Scene->Registry.valid(EntityHandle);
		}


		template<typename T>
		bool HasComponent() const
		{
			return m_Scene->Registry.has<T>(EntityHandle);
		}


		template<typename T>
		void RemoveComponent() const
		{
			BUBBLE_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->Registry.remove<T>(EntityHandle);
		}

		operator bool() const { return EntityHandle != entt::null; }

		bool operator== (const entt::entity& other) { return EntityHandle == other; }
	};

}
