
#include "scene_explorer.h"


namespace Bubble
{
	void SceneExplorerPanel::DrawEntitiesExplorer(bool* is_open_explorer, bool* is_open_properties,  Scene* scene)
	{
		if (*is_open_explorer)
		{
			ImGui::Begin("Scene explorer", is_open_explorer);

			scene->m_Registry.each([&](auto entityID)
				{
					Entity entity(entityID, scene);
					DrawEntityNode(entity);
				});

			if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
				SelectedEntity = {};
			}

			ImGui::End();
		}

		if (*is_open_properties)
		{
			ImGui::Begin("Properties", is_open_properties);
			if (SelectedEntity) {
				DrawComponents(SelectedEntity);
			}
		
			ImGui::End();
		}

	}

	void SceneExplorerPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

		if (ImGui::IsItemClicked())
		{
			SelectedEntity = entity;
		}

		//if (opened)
		//{
		//	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
		//	bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
		//	if (opened)
		//		ImGui::TreePop();
		//	ImGui::TreePop();
		//}

	}

	void SceneExplorerPanel::DrawComponents(Entity entity)
	{
		// Basic default properties

		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				auto& transform = entity.GetComponent<TransformComponent>().Transform;
				ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);
				ImGui::TreePop();
			}
		}

		// User properties
		for (auto DrawCustomProperties : CustomEntityProperties)
		{
			DrawCustomProperties(entity);
		}
	}
}