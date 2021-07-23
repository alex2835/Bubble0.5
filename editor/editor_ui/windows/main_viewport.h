#pragma once

#include "engine.h"
#include "ui_module.h"

namespace Bubble
{
	struct MainViewport : UIModule
	{
        MainViewport()
            : UIModule("Viewport")
        {
            mWindowFlags |= ImGuiWindowFlags_NoCollapse;
            mWindowFlags |= ImGuiWindowFlags_NoTitleBar;
        }
        
		void Draw(UIArgs args, DeltaTime dt) override
		{
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
            ImGui::Begin(mName.c_str(), &mIsOpen, mWindowFlags);
            {
                glm::vec2 viewport_size = args.mMainViewport->GetSize();
                ImVec2 imgui_viewport_size = ImGui::GetContentRegionAvail();

                uint32_t textureId    = args.mMainViewport->GetColorAttachmentRendererID();
                ImVec2   texture_size = ImVec2(args.mMainViewport->GetWidth(), args.mMainViewport->GetHeight());
                ImGui::Image((void*)textureId, texture_size, ImVec2(1, 1), ImVec2(0, 0));
                args.mMainViewport->mNewSize = *(glm::vec2*)&imgui_viewport_size;

                if (ImGui::IsItemHovered())
                {
                    args.mSceneCamera->OnUpdate(dt);
                }
            }
            ImGui::End();
            ImGui::PopStyleVar();
		}
        
        void OnUpdate(UIArgs args, DeltaTime dt) override
        {
            args.mMainViewport->OnUpdate();
        }

    };
}