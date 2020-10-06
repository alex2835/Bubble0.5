#pragma once

#include "scene.h"


namespace Bubble
{
	class Entity
	{
		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;

	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		
		template<typename T, typename... Args>
		T& EmplaceComponent(Args&&... args) const
		{
			BUBBLE_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}


		template<typename T, typename... Args>
		const Entity& AddComponent(Args&&... args) const
		{
			BUBBLE_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			return *this;
		}


		template<typename T>
		T& GetComponent() const
		{
			BUBBLE_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}


		template<typename T>
		bool HasComponent() const
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}


		template<typename T>
		void RemoveComponent() const
		{
			BUBBLE_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
	};

}
