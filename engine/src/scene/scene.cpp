
#include "scene.h"
#include "entity.h"
#include "components.h"

namespace Bubble
{

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = Entity(mRegistry.create(), this);
		auto& tag = entity.EmplaceComponent<TagComponent>();
		tag = name.empty() ? "Entity " + std::to_string((uint32_t)entity.mEntityHandle) : name;
		return entity;
	}

    void Scene::DeleteEntity(entt::entity entity)
    {
		mRegistry.destroy(entity);
    }

	void Scene::OnUpdate(DeltaTime dt)
	{
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{

	}

}