#pragma once

#include "engine.h"
#include "ui_module.h"

namespace Bubble
{
    enum class ComponentType { LIGHT, MODEL };

	struct EntityExplorer : UIModule
	{
		Entity mSelectedEntity;
        // UI state
        ComponentType mCurrentComponentComboBox = ComponentType::MODEL;

        inline EntityExplorer()
            : UIModule("Entity explorer")
        {}

		inline void Draw(UIArgs args, DeltaTime dt) override 
		{
            ImGui::Begin(mName.c_str(), &mIsOpen);
            {
                if (ImGui::Button("Create Entity", ImVec2(100, 25)))
                {
                    args.mScene->CreateEntity();
                }
                ImGui::SameLine();
                if (ImGui::Button("Delete Entity", ImVec2(100, 25)))
                {
                    if (mSelectedEntity)
                        args.mScene->DeleteEntity(mSelectedEntity.mEntityHandle);
                    mSelectedEntity = Entity();
                }

                args.mScene->mRegistry.each([&](auto entityID)
                    {
                        Entity entity(entityID, args.mScene);
            
                        auto& tag = entity.GetComponent<TagComponent>().mTag;
                        ImGui::Selectable(tag.c_str(), entity == mSelectedEntity);
            
                        if (ImGui::IsItemClicked())
                        {
                            mSelectedEntity = entity;
                        }
                    }
                );
            
                //if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered() ||
                //    args.mInput->IsKeyClick(SDLK_ESCAPE) && ImGui::IsWindowHovered())
                //{
                //    mSelectedEntity = {};
                //}
            }
            ImGui::End();
            
            ImGui::Begin("Properties");
            {
                if (mSelectedEntity)
                {
                    DrawComponents(mSelectedEntity, args);
                }
                //if (args.mInput->IsKeyClick(SDLK_ESCAPE) && ImGui::IsWindowHovered())
                //{
                //    mSelectedEntity = {};
                //}
            }
            ImGui::End();
        }


        void DrawComponents(Entity entity, UIArgs args)
        {
            auto& tag = entity.GetComponent<TagComponent>().mTag;

            // ================== Tag component ==================
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Tag component");

            ImGui::InputText("##TagInput", tag.data(), tag.capacity());
            ImGui::Separator();

            // ================= Transform component =================
            if (entity.HasComponent<TransformComponent>())
            {
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "Transform component");

                auto& transform = entity.GetComponent<TransformComponent>().mTransform;
                auto& position  = entity.GetComponent<PositionComponent>().mPosition;
                auto& rotation  = entity.GetComponent<RotationComponent>().mRotation;
                auto& scale     = entity.GetComponent<ScaleComponent>().mScale;

                bool  update = false;
                float scale_all = 0.0f;

                if (ImGui::DragFloat3("Position", (float*)&position, 0.1f))  update = true;
                if (ImGui::DragFloat3("Rotation", (float*)&rotation, 0.05f)) update = true;
                if (ImGui::Button("Restore rotation", { 120, 20 })) { update = true; rotation = glm::vec3(); }
                if (ImGui::DragFloat3("Scale", (float*)&scale, 0.05f))       update = true;
                if (ImGui::DragFloat("ScaleAll", &scale_all, 0.05f))         update = true;
                if (ImGui::Button("Restore scale", { 120, 20 })) { update = true; scale = glm::vec3(1.0f); }

                if (update)
                {
                    scale = glm::max(scale + scale_all, 0.01f);
                    transform = glm::mat4(1.0f);
                    transform = glm::translate(transform, position);
                    transform = glm::rotate(transform, rotation.x, glm::vec3(1, 0, 0));
                    transform = glm::rotate(transform, rotation.y, glm::vec3(0, 1, 0));
                    transform = glm::rotate(transform, rotation.z, glm::vec3(0, 0, 1));
                    transform = glm::scale(transform, scale);
                }
                ImGui::Separator();
            }

            // ================= Model component =================
            if (entity.HasComponent<ModelComponent>())
            {
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "Model component");
                ModelComponent& model_comp = entity.GetComponent<ModelComponent>();
                ImGui::Text("Current model: %s", model_comp->mRootNode->mName.c_str());

                int i = 0;
                int model_id = 0;
                std::string names;

                for (const auto& [path, model] : args.mLoader->mLoadedModels)
                {
                    if (model_comp == model)
                    {
                        model_id = i;
                    }
                    size_t pos = path.find_last_of("/") + 1;
                    size_t dpos = path.find_last_of(".");
                    std::string name = path.substr(pos, dpos - pos);
                    names += name + '\0';
                    i++;
                }
                ImGui::Combo("Models", &model_id, names.c_str());

                i = 0;
                for (const auto& [path, model] : args.mLoader->mLoadedModels)
                {
                    if (model_id == i)
                    {
                        model_comp = model;
                    }
                    i++;
                }

                if (ImGui::Button("Delete component ##Model", ImVec2(220, 20)))
                {
                    entity.DeleteComponent<TransformComponent>();
                    entity.DeleteComponent<PositionComponent>();
                    entity.DeleteComponent<RotationComponent>();
                    entity.DeleteComponent<ScaleComponent>();
                    entity.DeleteComponent<ModelComponent>();
                }
                ImGui::Separator();
            }

            // ===================== Light component ===================== 
            if (entity.HasComponent<LightComponent>())
            {
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "Light component");
                Light& light = entity.GetComponent<LightComponent>();

                const char* light_types_string = "Directional\0Point\0Spot\0";
                ImGui::Combo("Type", (int*)&light.Type, light_types_string);

                switch (light.Type)
                {
                    case LightType::DirLight:
                        ImGui::SliderFloat3("Direction", (float*)&light.Direction, -1.0f, 1.0f);
                        ImGui::ColorEdit3("Color", (float*)&light.Color);
                        ImGui::DragFloat("Brightness", (float*)&light.Brightness, 0.02f);
                        break;

                    case LightType::SpotLight:
                        ImGui::DragFloat3("Position", (float*)&light.Position, 0.05);
                        ImGui::SliderFloat3("Direction", (float*)&light.Direction, -1.0f, 1.0f);
                        ImGui::SliderFloat("Distance", (float*)&light.Distance, 0.0f, 1.0f);
                        ImGui::SliderFloat("Cutoff", (float*)&light.CutOff, 0.0f, 90.0f);
                        ImGui::SliderFloat("OuterCutoff", (float*)&light.OuterCutOff, 0.0f, 90.0f);
                        ImGui::ColorEdit3("Color", (float*)&light.Color);
                        ImGui::DragFloat("Brightness", (float*)&light.Brightness, 0.02f);
                        break;

                    case LightType::PointLight:
                        ImGui::DragFloat3("Position", (float*)&light.Position, 0.05f);
                        ImGui::SliderFloat("Distance", (float*)&light.Distance, 0.0f, 1.0f);
                        ImGui::ColorEdit3("Color", (float*)&light.Color);
                        ImGui::DragFloat("Brightness", (float*)&light.Brightness, 0.02f);
                        break;
                }
                if (ImGui::Button("Delete component ##Light", ImVec2(120, 20)))
                {
                    entity.DeleteComponent<LightComponent>();
                }
                ImGui::Separator();
            }


            // Add component
            ImGui::Dummy(ImVec2(0.0f, 10.0f));
            ImGui::TextColored(ImVec4(0, 1, 0, 1), "Add component");
            ImGui::Dummy(ImVec2(0.0f, 1.0f));

            const char* components_names = "Light component\0Model component\0";
            ImGui::Combo("Add component ##Combo", (int*)&mCurrentComponentComboBox, components_names);

            if (ImGui::Button("Add component ##Button", ImVec2(120, 25)) || args.mInput->IsKeyClick(SDLK_F1))
            {
                switch (mCurrentComponentComboBox)
                {
                    case Bubble::ComponentType::LIGHT:
                        entity.AddComponent<LightComponent>(Light::CreatePointLight());
                        break;
                    case Bubble::ComponentType::MODEL:
                        entity.AddComponent<PositionComponent>();
                        entity.AddComponent<RotationComponent>();
                        entity.AddComponent<ScaleComponent>();
                        entity.AddComponent<TransformComponent>(glm::mat4(1.0f));
                        entity.AddComponent<ModelComponent>(args.mLoader->LoadModel("resources/models/sphere.obj"));
                        break;
                    default:
                        BUBBLE_ASSERT(false, "Incorect component type");
                        break;
                }
            }

        }

	};
}