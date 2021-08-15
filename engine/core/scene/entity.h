#pragma once

#include "scene.h"

namespace Bubble
{
	struct Entity
	{
		entt::entity mEntityHandle = entt::null;
		Scene* mScene = nullptr;

		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;
		
		template<typename T, typename... Args>
		T& EmplaceComponent(Args&&... args) const
		{
            if (HasComponent<T>()) ReplaceComponent<T>();
			return mScene->mRegistry.emplace<T>(mEntityHandle, std::forward<Args>(args)...);
		}

		template<typename T, typename... Args>
		const Entity& AddComponent(Args&&... args) const
		{
			if (HasComponent<T>()) return *this;
			mScene->mRegistry.emplace<T>(mEntityHandle, std::forward<Args>(args)...);
			return *this;
		}

		template<typename T>
		auto& GetComponent() const
		{
			return mScene->mRegistry.get<T>(mEntityHandle);
		}

   		template<typename... Args>
   		auto GetComponents() const
   		{
   		    return mScene->mRegistry.get<Args...>(mEntityHandle);
   		}

   		template<typename T, typename... Args>
   		T& ReplaceComponent(Args... args) const
   		{
   		    return mScene->mRegistry.replace<T>(mEntityHandle, args...);
   		}

		template<typename T>
		void DeleteComponent() const
		{
		    mScene->mRegistry.remove<T>(mEntityHandle);
		}

		bool Valid()
		{
			return mScene && mScene->mRegistry.valid(mEntityHandle);
		}

		template<typename... Args>
		bool HasComponent() const
		{
			return mScene->mRegistry.has<Args...>(mEntityHandle);
		}


		template<typename T>
		void RemoveComponent() const
		{
			BUBBLE_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			mScene->mRegistry.remove<T>(mEntityHandle);
		}

		operator bool() const { return mEntityHandle != entt::null; }

		bool operator== (const entt::entity& other) { return mEntityHandle == other; }
		bool operator== (const Entity& other) { return mEntityHandle == other.mEntityHandle; }
	};

}
