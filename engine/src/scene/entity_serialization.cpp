
#include "entity_serialization.h"


namespace Bubble
{
	// ================= Archives ===================
	struct OutputArchive
	{
		nlohmann::json Json;

		void operator()(entt::entity entity)
		{
			Json["Entities"].push_back((uint32_t)entity);
		}

		void operator()(std::underlying_type_t<entt::entity> size)
		{
			Json["Size"].push_back(size);
		}

		template <typename T>
		void operator() (entt::entity entity, const T& component)
		{
			nlohmann::json entity_component;
			entity_component["Entity"] = entity;
			entity_component["Component"] = component.Serialize();
			Json["Components"].push_back(entity_component);
		};

	};

	struct InputArchive
	{
		nlohmann::json Json;
		int EtityIndex = 0;
		int SizeIndex = 0;
		int ComponetIndex = 0;

		void operator()(entt::entity& entity)
		{
			entity = Json["Entities"][EtityIndex++];
		}

		void operator()(std::underlying_type_t<entt::entity>& size)
		{
			size = Json["Size"][SizeIndex++];
		}
		 
		template <typename T>
		void operator() (entt::entity& entity, T& component)
		{
			nlohmann::json entity_component = Json["Components"][ComponetIndex++];
			entity = entity_component["Entity"];
			component.Deserialize(entity_component["Component"]);
		};

	};

	// ==================== Serialization ======================
	nlohmann::json SerializeScene(const entt::registry& scene)
	{
		OutputArchive output;
		entt::snapshot{ scene }
			.entities(output)
			.component<TagComponent, PositionComponent, RotationComponent, ScaleComponent, TransformComponent, LightComponent, ModelComponent>(output);
		return output.Json;
	}

	void DeserializeScene(entt::registry& scene, const nlohmann::json& json)
	{
		InputArchive input{ json };
		scene.clear();

		entt::snapshot_loader{ scene }
			.entities(input)
			.component<TagComponent, PositionComponent, RotationComponent, ScaleComponent, TransformComponent, LightComponent, ModelComponent>(input)
			.orphans();
	}

}