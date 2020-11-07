
#include "scene_explorer.h"


namespace Bubble
{
	void SceneExplorer::Draw(bool* is_open_explorer, bool* is_open_properties,  Scene* scene)
	{
		if (*is_open_explorer)
		{
			ImGui::Begin("Scene explorer", is_open_explorer);
		
			scene->Registry.each([&](auto entityID)
				{
					Entity entity(entityID, scene);

					auto& tag = entity.GetComponent<TagComponent>().mTag;
					ImGui::Selectable(tag.c_str(), entity == SelectedEntity);

					if (ImGui::IsItemClicked())
					{
						SelectedEntity = entity;
					}
				});

			if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered() ||
				Input::IsKeyClick(SDLK_ESCAPE) && ImGui::IsWindowHovered())
			{
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
			
			if (Input::IsKeyClick(SDLK_ESCAPE) && ImGui::IsWindowHovered())
			{
				SelectedEntity = {};
			}
			ImGui::End();
		}

	}


	void SceneExplorer::DrawComponents(Entity entity)
	{
		// =============== Basic properties =================

		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().mTag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("Name", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
			ImGui::Separator();
		}


		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				auto& transform = entity.GetComponent<TransformComponent>().mTransform;
				auto& position = entity.GetComponent<PositionComponent>().mPosition;
				auto& rotation = entity.GetComponent<RotationComponent>().mRotation;
				auto& scale = entity.GetComponent<ScaleComponent>().mScale;

				bool update = false;
				float scale_entire = 0.0f;

				if (ImGui::DragFloat3("Position", (float*)&position, 0.1f)) update = true;
				if (ImGui::DragFloat3("Rotation", (float*)&rotation, 0.05f)) update = true;
				if (ImGui::Button("Restore rotation", { 120, 20 })) { update = true; rotation = glm::vec3(); }
				if (ImGui::DragFloat3("Scale", (float*)&scale, 0.05f)) update = true;
				if (ImGui::DragFloat("ScaleAll", &scale_entire, 0.05f)) update = true;
				if (ImGui::Button("Restore scale", { 120, 20 })) { update = true; scale = glm::vec3(1.0f); }

				if (update)
				{
					scale = glm::max(scale + scale_entire, 0.01f);
					transform = glm::mat4(1.0f);
					transform = glm::translate(transform, position);
					transform = glm::rotate(transform, rotation.x, glm::vec3(1, 0, 0));
					transform = glm::rotate(transform, rotation.y, glm::vec3(0, 1, 0));
					transform = glm::rotate(transform, rotation.z, glm::vec3(0, 0, 1));
					transform = glm::scale(transform, scale);
				}

				ImGui::TreePop();
			}
			ImGui::Separator();
		}


		if (entity.HasComponent<LightComponent>())
		{
			Light& light = entity.GetComponent<LightComponent>().mLight;
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
					if (ImGui::SliderFloat("Distance", (float*)&light.Distance, 0.0f, 1.0f)) {
						light.SetDistance();
					}
					ImGui::SliderFloat("Cutoff", (float*)&light.CutOff, 0.0f, 20.0f);
					ImGui::SliderFloat("OuterCutoff", (float*)&light.OuterCutOff, 0.0f, 20.0f);
					ImGui::ColorEdit3("Color", (float*)&light.Color);
					ImGui::SliderFloat("Brightness", (float*)&light.Brightness, 0.0f, 1.0f);
					ImGui::Separator();
				break;

				case LightType::PointLight:
					ImGui::Text("PointLight");
					if (ImGui::SliderFloat("Distance", (float*)&light.Distance, 0.0f, 1.0f)) {
						light.SetDistance();
					}
					ImGui::ColorEdit3("Color", (float*)&light.Color);
					ImGui::SliderFloat("Brightness", (float*)&light.Brightness, 0.0f, 1.0f);
					ImGui::Separator();
				break;
			}
		}
	}

}