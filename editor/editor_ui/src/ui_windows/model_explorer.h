#pragma once

#include "engine.h"

#include "tools/file_dialog.h"
#include "ui_module.h"
#include "viewport.h"
#include <algorithm>
using namespace std::string_literals;

namespace Bubble
{
	struct ModelExplorer : UIModule
    {
        ThirdPersonCamera mCamera;
		Ref<Model>        mSelectedModel;
		Viewport          mViewport;
		Light             mLight;
	
        inline ModelExplorer()
            : UIModule("Model explorer"),
              mSelectedModel(nullptr),
              mViewport(800, 600),
			  mCamera(0)
        {
            mLight  = Light::CreateDirLight();
        }
		
		inline void Draw(UIArgs args, DeltaTime dt)
		{
            ImGui::Begin("Models explorer", &mIsOpen);
            {
                ImVec2 window_size = ImGui::GetContentRegionAvail();
                ImVec2 window_pos  = ImGui::GetCursorScreenPos();

                // ==================== Viewport input ====================
                {
                    ImVec2 viewport_size = ImVec2(window_size.x * 0.7f, window_size.y * 0.75f);
                    // Invisible drag able area over the viewport
                    ImGui::InvisibleButton("##dummy", viewport_size);

                    // Moving by dragging
                    if (ImGui::IsItemActive() && ImGui::IsMouseDragging(0))
                    {
                        mCamera.ProcessMouseMovementShift(args.mInput->fGetMouseRelX(), -args.mInput->fGetMouseRelY());
                        mCamera.Update(dt);
                    }
                    // Change radius by mouse wheel scrolling
                    if (ImGui::IsWindowHovered())
                    {
                        if (mSelectedModel)
                        {
                            float longest_edge = mSelectedModel->mBoundingBox.getLongestEdge();
                            mCamera.Radius -= args.mInput->GetMouseWheelOffset() * longest_edge / 5;
                            mCamera.Radius = glm::clamp(mCamera.Radius, longest_edge, mCamera.Far);
                            mCamera.Update(dt);
                        }
                    }
                    //  ================= Render model =================
                    if (mSelectedModel && ImGui::IsItemVisible())
                    {
                        RenderSelectedModel(args.mRenderer);
                    }
                    // ==================== Draw viewport ==================== 
                    uint32_t textureId = mViewport.GetColorAttachmentRendererID();
                    ImVec2   texture_size = ImVec2(window_pos.x + viewport_size.x, window_pos.y + viewport_size.y);
                    ImGui::GetWindowDrawList()->AddImage((void*)textureId, window_pos, texture_size, ImVec2(1, 1), ImVec2(0, 0));
                    mViewport.mNewSize = *(glm::vec2*)&viewport_size;
                }

                // ==================== Model info ====================
                ImGui::SameLine();
                ImGui::BeginChild("Model info", ImVec2(0, window_size.y * 0.75f), true);
                {
                    if (mSelectedModel)
                    {
                        ImGui::Text("Meshes: %d", mSelectedModel->mMeshes.size());
                        int i = 0;
                        for (auto& mesh : mSelectedModel->mMeshes)
                        {
                            i++;
                            auto node_name = "node" + std::to_string(i);
                            if (ImGui::TreeNode(node_name.c_str(), mesh.mName.c_str()))
                            {
                                ImVec2 image_size(100, 100);

                                ImGui::Text("Diffuse "); ImGui::SameLine();
                                ImGui::Image((ImTextureID)mesh.mMaterial.Diffuse.mRendererID,  image_size);
                                if (ImGui::IsItemClicked())
                                {
                                    try {
                                        std::string path = OpenFileDialog("png,jpg,tga");
                                        mesh.mMaterial.Diffuse = Texture2D(path);
                                    }
                                    catch (const std::exception& e)
                                    {
                                        LOG_ERROR("Diffuse map can't be opened");
                                    }
                                }

                                ImGui::Text("Specular"); ImGui::SameLine();
                                ImGui::Image((ImTextureID)mesh.mMaterial.Specular.mRendererID, image_size);
                                if (ImGui::IsItemClicked())
                                {
                                    try {
                                        std::string path = OpenFileDialog("png,jpg,tga");
                                        mesh.mMaterial.Specular = Texture2D(path);
                                    }
                                    catch (const std::exception& e)
                                    {
                                        LOG_ERROR("Specular map can't be opened");
                                    }
                                }

                                ImGui::Text("Diffuse "); ImGui::SameLine();
                                ImGui::Image((ImTextureID)mesh.mMaterial.Normal.mRendererID, image_size);
                                if (ImGui::IsItemClicked())
                                {
                                    try {
                                        std::string path = OpenFileDialog("png,jpg,tga");
                                        mesh.mMaterial.Normal = Texture2D(path);
                                    }
                                    catch (const std::exception& e)
                                    {
                                        LOG_ERROR("Normal map can't be opened");
                                    }
                                }
                                
                                ImGui::TreePop();
                            }
                        }
                    }
                }
                ImGui::EndChild();

                // ===================== Model list =====================
                ImGui::BeginChild("Models list", ImVec2(window_size.x * 0.5f, window_size.y * 0.24f), true);
                {
                    for (const auto& [path, model] : args.mLoader->mLoadedModels)
                    {
                        size_t pos = path.find_last_of("/") + 1;
                        std::string name = path.substr(pos);

                        ImGui::Selectable(name.c_str(), mSelectedModel == model);

                        // Switch
                        if (ImGui::IsItemClicked())
                        {
                            mSelectedModel = model;
                            // Start camera params for this model
                            mCamera.Center = mSelectedModel->mBoundingBox.getCenter();
                            mCamera.Radius = mSelectedModel->mBoundingBox.getLongestEdge() * 1.5f;
                            mCamera.Update(dt);
                        }
                    }

                    if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
                        mSelectedModel = nullptr;
                    }
                }
                ImGui::EndChild();


                // ==================== Buttons ====================
                ImGui::SameLine();
                if (ImGui::Button("Load", { 100, window_size.y * 0.05f }))
                {
                    try
                    {
                        std::string path = OpenFileDialog();
                        args.mLoader->LoadModel(path);
                    }
                    catch (const std::exception& e)
                    {
                        LOG_ERROR(e.what());
                    }
                }

            }
            ImGui::End();
		}

        void OnUpdate(UIArgs args, DeltaTime dt) override
        {
            mViewport.OnUpdate();
        }


	private:
		inline void RenderSelectedModel(Renderer* renderer)
		{
            renderer->SetViewport(mViewport);
            renderer->SetCamera(mCamera);
            renderer->SetLights(&mLight, 1);
            
            renderer->SetClearColor(glm::vec4(0.4f));
            renderer->Clear();
            
            renderer->DrawModel(mSelectedModel, glm::mat4(1.0f), renderer->mStorage.mPhongShader);
		}
    
    };

}