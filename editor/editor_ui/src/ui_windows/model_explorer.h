#pragma once

#include "engine.h"

#include "tools/file_dialog.h"
#include "ui_module.h"
#include "viewport.h"

#include <algorithm>


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
                ImVec2 pos = ImGui::GetCursorScreenPos();

                // ==================== Viewport input ==================== 
                // Invisible drag able area over the viewport
                ImGui::InvisibleButton("##dummy", ImVec2{ window_size.x + 1, window_size.y * 0.7f + 1 });

                // Moving by dragging
                if (ImGui::IsItemActive() && ImGui::IsMouseDragging(0))
                {
                    mCamera.ProcessMouseMovementShift(args.mInput->fGetMouseRelX(), -args.mInput->fGetMouseRelY());
                    mCamera.Update(dt);
                }

                // Change radius by mouse wheel scrolling
                if (ImGui::IsWindowFocused())
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
                if (mSelectedModel && ImGui::IsItemVisible()) {
                    RenderSelectedModel(args);
                }
                // ==================== Draw viewport ==================== 
                uint32_t textureId = mViewport.GetColorAttachmentRendererID();
                ImGui::GetWindowDrawList()->AddImage((void*)textureId, pos, ImVec2{ pos.x + window_size.x, pos.y + window_size.y * 0.7f }, ImVec2(1, 1), ImVec2(0, 0));

                mViewport.mNewSize = { window_size.x, window_size.y * 0.6f };


                // ==================== Model list ====================
                ImGui::BeginChild("Models list", ImVec2(0, window_size.y * 0.2f), true);
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

                // ==================== Info ====================
                // ...


                // ==================== Buttons ====================

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
		inline void RenderSelectedModel(UIArgs args)
		{
            args.mRenderer->SetViewport(mViewport);
            args.mRenderer->SetCamera(mCamera);
            args.mRenderer->SetLights(&mLight, 1);
            
            args.mRenderer->SetClearColor(glm::vec4(0.4f));
            args.mRenderer->Clear();
            
            args.mRenderer->DrawModel(mSelectedModel, glm::mat4(1.0f), args.mRenderer->mStorage.mPhongShader);
            // Temp
            //Viewport::BindWindow(args.mInput->mWindow);
		}
    
    };

}