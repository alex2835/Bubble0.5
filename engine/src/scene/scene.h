#pragma once

#include "base.h"
#include "time/time.h"

#include "entt/entt.hpp"


namespace Bubble
{
	class Entity;

	class Scene
	{
	public:
		entt::registry Registry;
		friend class Entity;

	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());

		void OnUpdate(DeltaTime delta_time);
		void OnViewportResize(uint32_t width, uint32_t height);

		template <typename ...Args>
		auto GetView()
		{
			return Registry.view<Args...>();
		}

	};
}