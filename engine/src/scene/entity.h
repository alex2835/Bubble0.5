#pragma once

#include "scene.h"

namespace Bubble
{
	class Entity
	{
		entt::entity EntityHandle = entt::null;
		Scene* mScene = nullptr;

	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		
		template<typename T, typename... Args>
		T& EmplaceComponent(Args&&... args) const
		{
			BUBBLE_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return mScene->mRegistry.emplace<T>(EntityHandle, std::forward<Args>(args)...);
		}


		template<typename T, typename... Args>
		const Entity& AddComponent(Args&&... args) const
		{
			BUBBLE_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			mScene->mRegistry.emplace<T>(EntityHandle, std::forward<Args>(args)...);
			return *this;
		}

		template<typename T>
		auto& GetComponent() const
		{
			return mScene->mRegistry.get<T>(EntityHandle);
		}

        template<typename... Args>
        auto GetComponents() const
        {
            return mScene->mRegistry.get<Args...>(EntityHandle);
        }

		bool Valid()
		{
			return mScene && mScene->mRegistry.valid(EntityHandle);
		}


		template<typename... Args>
		bool HasComponent() const
		{
			return mScene->mRegistry.has<Args...>(EntityHandle);
		}


		template<typename T>
		void RemoveComponent() const
		{
			BUBBLE_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			mScene->mRegistry.remove<T>(EntityHandle);
		}

		operator bool() const { return EntityHandle != entt::null; }

		bool operator== (const entt::entity& other) { return EntityHandle == other; }
		bool operator== (const Entity& other) { return EntityHandle == other.EntityHandle; }
	};

}
