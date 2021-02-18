#pragma once

#include "engine.h"
#include "ui_module.h"
#include "tools/file_dialog.h"
#include "viewport.h"


namespace Bubble
{
	struct SkyboxExplorer : UIModule
	{
		Ref<Skybox> mSelectedSkybox;
		FreeCamera  mCamera;
        Viewport    mViewport;

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
                ImVec2 window_pos  = ImGui::GetCursorScreenPos();
                ImVec2 window_size = ImGui::GetContentRegionAvail();

                // ==================== Viewport input ==================== 
                {
                    ImVec2 viewport_size = ImVec2(window_size.x, window_size.y * 0.75f);
                    // Invisible drag able area over the viewport
                    ImGui::InvisibleButton("##dummy", viewport_size);

                    // Moving by dragging
                    if (ImGui::IsItemActive() && ImGui::IsMouseDragging(0))
                    {
                        mCamera.ProcessMouseMovementShift(args.mInput->fGetMouseRelX(), args.mInput->fGetMouseRelY());
                        mCamera.Update(dt);
                    }
                    //  ================= Render model =================
                    if (mSelectedSkybox && ImGui::IsItemVisible())
                    {
                        RenderSelectedSkybox(args.mRenderer);
                    }
                    // ==================== Draw viewport ==================== 
                    uint32_t textureId = mViewport.GetColorAttachmentRendererID();
                    ImVec2   texture_size = ImVec2(window_pos.x + viewport_size.x, window_pos.y + viewport_size.y);
                    ImGui::GetWindowDrawList()->AddImage((void*)textureId, window_pos, texture_size, ImVec2(1, 1), ImVec2(0, 0));
                    mViewport.mNewSize = *(glm::vec2*)&viewport_size;
                }

                // ==================== Model list ====================
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

                // ==================== Buttons ====================
                ImGui::SameLine();
                if (ImGui::Button("Load", { 100, window_size.y * 0.05f }))
                {
                    try
                    {
                        std::string path = OpenFileDialog();
                        args.mLoader->LoadSkybox(path);
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

    };
}