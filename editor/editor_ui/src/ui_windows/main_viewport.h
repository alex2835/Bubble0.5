#pragma once

#include "ui_module.h"
#include "viewport.h"

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
        
		void Draw(UIArgs args, DeltaTime time) override
		{
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
            ImGui::Begin("Viewport", &mIsOpen, mWindowFlags);
            {
                ImVec2 imgui_viewport_size = ImGui::GetContentRegionAvail();
                glm::vec2 viewport_size = args.mMainViewport->GetSize();

                uint32_t textureId = args.mMainViewport->GetColorAttachmentRendererID();
                ImGui::Image((void*)textureId, ImVec2{ (float)args.mMainViewport->GetWidth(), (float)args.mMainViewport->GetHeight() }, ImVec2(1, 1), ImVec2(0, 0));

                args.mMainViewport->mNewSize = *(glm::vec2*)&imgui_viewport_size;
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