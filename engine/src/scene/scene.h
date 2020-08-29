#pragma once

#include "base.h"
#include "delta_time/delta_time.h"

#include "entt/entt.hpp"


namespace Bubble
{
	class Entity;

	class Scene
	{
		entt::registry m_Registry;
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
			return m_Registry.view<Args...>();
		}

	};
}