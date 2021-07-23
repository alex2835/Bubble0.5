#pragma once

#include "base/base.h"
#include "base/timer.h"
#include "entt/entt.hpp"

namespace Bubble
{
	class Entity;

	class Scene
	{
	public:
		entt::registry mRegistry;
		friend class Entity;

	public:
		Scene();
		~Scene();
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;
		Scene(Scene&&) = delete;
		Scene& operator=(Scene&&) = delete;

		Entity CreateEntity(const std::string& name = std::string());
		void DeleteEntity(entt::entity entity);

		void OnUpdate(DeltaTime delta_time);
		void OnViewportResize(uint32_t width, uint32_t height);

		template <typename ...Args>
		auto GetView() { return mRegistry.view<Args...>(); }
	};

}