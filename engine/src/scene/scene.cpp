
#include "scene.h"
#include "entity/entity.h"
#include "entity/scriptable_entity.h"
#include "components/basic_components.h"


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
		Entity entity = { m_Registry.create(), this };
		auto& tag = entity.EmplaceComponent<TagComponent>();
		tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(DeltaTime dt)
	{
		// update native scripts
		m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
			{
				if (!nsc.Instance)
				{
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_Entity = Entity{ entity, this };
					nsc.Instance->OnCreate();
				}

				nsc.Instance->OnUpdate(dt);
			}
		);
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{

	}

}