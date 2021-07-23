#pragma once

#include "engine.h"
#include "ui_module.h"
#include "tools/file_dialog.h"

namespace Bubble
{
	struct SkyboxExplorer : UIModule
	{
        FreeCamera  mCamera;
        Viewport    mViewport;
        Ref<Skybox>    mSelectedSkybox;
        Ref<Texture2D> mSelectedSkysphere;

        inline SkyboxExplorer()
            : UIModule("Skybox explorer"),
              mSelectedSkybox(nullptr),
              mViewport(800, 600)
        {
            mCamera.Fov = PI / 3;
        }
        
		inline void Draw(UIArgs args, DeltaTime dt) override
		{
            ImGui::Begin(mName.c_str(), &mIsOpen);
            {
                ImVec2 window_size = ImGui::GetContentRegionAvail();
                
                // ================= Draw viewport =================
                uint32_t textureId   = mViewport.GetColorAttachmentRendererID();
                ImVec2 viewport_size = ImVec2(window_size.x, window_size.y * 0.75f);
                
                ImGui::Image((void*)textureId, viewport_size, ImVec2(1, 1), ImVec2(0, 0));
                mViewport.mNewSize = *(glm::vec2*)&viewport_size;
                
                //  ================= Render skies =================
                if (ImGui::IsItemVisible())
                {
                    switch (args.mRenderer->mSceneStage.mBackgroundType)
                    {
                        case BackgroundType::COLOR:
                            RenderSelectedColor(args.mRenderer);
                            break;
                        case BackgroundType::SKYBOX:
                            if (mSelectedSkybox)
                                RenderSelectedSkybox(args.mRenderer);
                            break;
                        case BackgroundType::SKYSPHERE:
                            if (mSelectedSkysphere)
                                RenderSelectedSkysphere(args.mRenderer);
                            break;
                    }
                }
                // Moving by dragging
                if (ImGui::IsWindowFocused() && ImGui::IsMouseDragging(0))
                {
                    mCamera.ProcessMouseMovementShift(args.mInput->fGetMouseRelX(), args.mInput->fGetMouseRelY());
                    mCamera.Update(dt);
                }

                // ==================== Skies list ====================
                switch (args.mRenderer->mSceneStage.mBackgroundType)
                {
                    case BackgroundType::SKYBOX:
                        DrawSkyboxList(window_size, args, dt);
                        break;
                    case BackgroundType::SKYSPHERE:
                        DrawSkysphereList(window_size, args, dt);
                        break;
                }

            }
            ImGui::End();
		}

        void OnUpdate(UIArgs args, DeltaTime dt) override
        {
            mViewport.OnUpdate();
        }

    private:
        inline void RenderSelectedColor(Renderer* renderer)
        {
            renderer->SetViewport(mViewport);
            renderer->SetCamera(mCamera);
            renderer->Clear();
        }

        inline void RenderSelectedSkybox(Renderer* renderer)
        {
            renderer->SetViewport(mViewport);
            renderer->SetCamera(mCamera);
            renderer->ClearDepth();

            glm::mat4 view = Skybox::GetViewMatrix(mCamera.GetLookatMat());
            (*renderer->mUBOProjectionView)[0].SetMat4("View", view);

            renderer->mStorage.mSkyboxShader->SetUni1f("u_Brightness",  1.0f);
            renderer->mStorage.mSkyboxShader->SetUni1f("u_BlendFactor", 0.0f);

            renderer->DrawSkybox(&mSelectedSkybox, 1, renderer->mStorage.mSkyboxShader);
        }

        inline void RenderSelectedSkysphere(Renderer* renderer)
        {
            renderer->SetViewport(mViewport);
            renderer->SetCamera(mCamera);
            renderer->ClearDepth();

            glm::mat4 view = Skybox::GetViewMatrix(mCamera.GetLookatMat());
            (*renderer->mUBOProjectionView)[0].SetMat4("View", view);

            renderer->DrawSkysphere(mSelectedSkysphere);
        }

        inline void DrawSkyboxList(ImVec2 window_size, UIArgs args, DeltaTime dt)
        {
            ImGui::BeginChild("Skybox list", ImVec2(window_size.x * 0.5f, window_size.y * 0.24f), true);
            {
                for (const auto& [path, skybox] : args.mLoader->mLoadedSkyboxes)
                {
                    size_t pos = path.find_last_of("/") + 1;
                    std::string name = path.substr(pos);

                    ImGui::Selectable(name.c_str(), mSelectedSkybox == skybox);
                    if (ImGui::IsItemClicked())
                    {
                        mSelectedSkybox = skybox;
                        mCamera.Update(dt);
                    }
                }
                if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
                {
                    mSelectedSkybox = nullptr;
                }
            }
            ImGui::EndChild();

            // Buttons
            ImGui::SameLine();
            if (ImGui::Button("Load", ImVec2(100, window_size.y * 0.05f)))
            {
                try {
                    std::string path = OpenFileDialog();
                    args.mLoader->LoadSkybox(path);
                }
                catch (const std::exception& e)
                {
                    LOG_ERROR(e.what());
                }
            }
        }

        inline void DrawSkysphereList(ImVec2 window_size, UIArgs args, DeltaTime dt)
        {
            ImGui::BeginChild("Skysphere list", ImVec2(window_size.x * 0.5f, window_size.y * 0.24f), true);
            {
                for (const auto& [path, skysphere] : args.mLoader->mLoadedSkypsheres)
                {
                    size_t pos = path.find_last_of("/") + 1;
                    std::string name = path.substr(pos);

                    ImGui::Selectable(name.c_str(), mSelectedSkysphere == skysphere);
                    if (ImGui::IsItemClicked())
                    {
                        mSelectedSkysphere = skysphere;
                        mCamera.Update(dt);
                    }
                }
                if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
                {
                    mSelectedSkysphere = nullptr;
                }
            }
            ImGui::EndChild();

            // Buttons
            ImGui::SameLine();
            if (ImGui::Button("Load", ImVec2(100, window_size.y * 0.05f)))
            {
                try {
                    std::string path = OpenFileDialog();
                    args.mLoader->LoadSkysphere(path);
                }
                catch (const std::exception& e)
                {
                    LOG_ERROR(e.what());
                }
            }
        }
    };
}