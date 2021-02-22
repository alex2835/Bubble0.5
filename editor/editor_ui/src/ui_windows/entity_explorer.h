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
            
                if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered() ||
                    args.mInput->IsKeyClick(SDLK_ESCAPE) && ImGui::IsWindowHovered())
                {
                    mSelectedEntity = {};
                }
            }
            ImGui::End();
            
            ImGui::Begin("Properties");
            {
                if (mSelectedEntity) {
                    DrawComponents(mSelectedEntity, args);
                }
            
                if (args.mInput->IsKeyClick(SDLK_ESCAPE) && ImGui::IsWindowHovered())
                {
                    mSelectedEntity = {};
                }
            }
ImGui::End();
        }

        void DrawComponents(Entity entity, UIArgs args)
        {
            auto& tag = entity.GetComponent<TagComponent>().mTag;

            // ==================== Tag component ====================
            if (ImGui::InputText("Tag", tag.data(), tag.capacity()))
            {
            }
            ImGui::Separator();

            // ================= Transform component =================
            if (entity.HasComponent<TransformComponent>())
            {
                if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
                {
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

                    ImGui::TreePop();
                }
                ImGui::Separator();
            }

            // ===================== Light component ===================== 
            if (entity.HasComponent<LightComponent>())
            {
                Light& light = entity.GetComponent<LightComponent>();
                switch (light.Type)
                {
                case LightType::DirLight:
                    ImGui::Text("Global light");
                    ImGui::SliderFloat3("Direction", (float*)&light.Direction, -1.0f, 1.0f);
                    ImGui::ColorEdit3("Color", (float*)&light.Color);
                    ImGui::DragFloat("Brightness", (float*)&light.Brightness, 0.02f);
                    ImGui::Separator();
                    break;

                case LightType::SpotLight:
                    ImGui::Text("Spotlight");
                    ImGui::DragFloat3("Position", (float*)&light.Position, 0.05);
                    ImGui::SliderFloat3("Direction", (float*)&light.Direction, -1.0f, 1.0f);
                    ImGui::SliderFloat("Distance", (float*)&light.Distance, 0.0f, 1.0f);
                    ImGui::SliderFloat("Cutoff", (float*)&light.CutOff, 0.0f, 90.0f);
                    ImGui::SliderFloat("OuterCutoff", (float*)&light.OuterCutOff, 0.0f, 90.0f);
                    ImGui::ColorEdit3("Color", (float*)&light.Color);
                    ImGui::DragFloat("Brightness", (float*)&light.Brightness, 0.02f);
                    ImGui::Separator();
                    break;

                case LightType::PointLight:
                    ImGui::Text("PointLight");
                    ImGui::DragFloat3("Position", (float*)&light.Position, 0.05f);
                    ImGui::SliderFloat("Distance", (float*)&light.Distance, 0.0f, 1.0f);
                    ImGui::ColorEdit3("Color", (float*)&light.Color);
                    ImGui::DragFloat("Brightness", (float*)&light.Brightness, 0.02f);
                    ImGui::Separator();
                    break;
                }
                ImGui::Separator();
            }

            // Model component
            if (entity.HasComponent<ModelComponent>())
            {
                ModelComponent& model = entity.GetComponent<ModelComponent>();
                ImGui::Text("Current model: %s", model->mRootNode->mName.c_str());
            }
            ImGui::Separator();


            // Add component
            const char* components_names = "Light component\0Model component";
            ImGui::Combo("Type", (int*)&mCurrentComponentComboBox, components_names, 2);
            if (ImGui::Button("Add component", ImVec2(100, 25)))
            {
                switch (mCurrentComponentComboBox)
                {
                    case Bubble::ComponentType::LIGHT:
                        entity.AddComponent<LightComponent>(Light::CreatePointLight());
                        break;
                    case Bubble::ComponentType::MODEL:
                        entity.AddComponent<TransformComponent>();
                        entity.AddComponent<PositionComponent>();
                        entity.AddComponent<RotationComponent>();
                        entity.AddComponent<ScaleComponent>();
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