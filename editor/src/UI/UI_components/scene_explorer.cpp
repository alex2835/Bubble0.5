
#include "scene_explorer.h"


namespace Bubble
{
	void SceneExplorer::Draw(bool* is_open_explorer, bool* is_open_properties,  Scene* scene)
	{
		if (*is_open_explorer)
		{
			ImGui::Begin("Scene explorer", is_open_explorer);
		
			scene->m_Registry.each([&](auto entityID)
				{
					Entity entity(entityID, scene);

					auto& tag = entity.GetComponent<TagComponent>().Tag;
					ImGui::Selectable(tag.c_str());

					if (ImGui::IsItemClicked())
					{
						SelectedEntity = entity;
					}
					
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


	void SceneExplorer::DrawComponents(Entity entity)
	{
		// =============== Basic default properties =================

		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			ImGui::Text("Name");
			if (ImGui::InputText("", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
			ImGui::Separator();
		}

		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				auto& transform = entity.GetComponent<TransformComponent>().Transform;
				ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);
				ImGui::TreePop();
			}
			ImGui::Separator();
		}

		if (entity.HasComponent<Light>())
		{
			Light& light = entity.GetComponent<Light>();
			switch(light.Type)
			{
				case LightType::DirLight:
					ImGui::Text("Global light");
					ImGui::SliderFloat3("Direction", (float*)&light.Direction, -1.0f, 1.0f);
					ImGui::SliderFloat("Brightness", (float*)&light.Brightness, 0.0f, 1.0f);
					ImGui::ColorEdit3("Color", (float*)&light.Color);
					ImGui::Separator();
				break;

				case LightType::SpotLight:
					ImGui::Text("Spotlight");
					ImGui::SliderFloat("Distance", (float*)&light.Distance, 0.0f, 1.0f);
					ImGui::SliderFloat("Cutoff", (float*)&light.CutOff, 0.0f, 20.0f);
					ImGui::SliderFloat("OuterCutoff", (float*)&light.OuterCutOff, 0.0f, 20.0f);
					ImGui::ColorEdit3("Color", (float*)&light.Color);
					ImGui::SliderFloat("Brightness", (float*)&light.Brightness, 0.0f, 1.0f);
					ImGui::Separator();
				break;

				case LightType::PointLight:
					ImGui::Text("PointLight");
					ImGui::SliderFloat("Distance", (float*)&light.Distance, 0.0f, 1.0f);
					ImGui::ColorEdit3("Color", (float*)&light.Color);
					ImGui::SliderFloat("Brightness", (float*)&light.Brightness, 0.0f, 1.0f);
					ImGui::Separator();
				break;
			}
		}


		// ================ User properties ==================
		//for (auto DrawCustomProperties : CustomEntityProperties)
		//{
		//	DrawCustomProperties(entity);
		//}
	}
}