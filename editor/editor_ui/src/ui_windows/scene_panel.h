#pragma once

#include "engine.h"
#include "ui_module.h"


namespace Bubble
{
	struct ScenePanel : UIModule
	{
		// Skybox
        int SelectedSkyboxFirstID = 0;
        int SelectedSkyboxSecondID = 0;
        std::string SelectedSkyboxNameFirst;
        std::string SelectedSkyboxNameSecond;

        inline ScenePanel()
            : UIModule("Scene panel")
        {}

		inline void Draw(UIArgs args, DeltaTime dt) override
		{
            //ImGui::Begin("Scene panel", &mIsOpen);
            //{
            //    int i = 0;
            //    std::string names;
            //
            //    for (const auto& [path, skybox] : *Loader::sLoadedSkyboxes)
            //    {
            //        if (i == SelectedSkyboxFirstID)
            //        {
            //            SelectedSkyboxNameFirst = path;
            //        }
            //        if (i == SelectedSkyboxSecondID)
            //        {
            //            SelectedSkyboxNameSecond = path;
            //        }
            //
            //        size_t start_pos = path.find_last_of("/") + 1;
            //        size_t end_pos = path.find_last_of(".");
            //        std::string name = path.substr(start_pos, end_pos - start_pos);
            //        names += name + '\0';
            //        i++;
            //    }
            //
            //    // Skyboxes
            //    ImVec2 window_size = ImGui::GetContentRegionAvail();
            //    ImGui::BeginChild("Active skyboxes", ImVec2(0, window_size.y * 0.2f), true);
            //    {
            //        ImGui::SliderFloat("Brightness", &Renderer::sSkyboxBrightness, 0.0f, 1.0f);
            //        ImGui::SliderFloat("Blend factor", &Renderer::sSkyboxBlendFactor, 0.0f, 1.0f);
            //        ImGui::SliderFloat("Rotation", &Renderer::sSkyboxRotationSpeed, 0.0001f, 0.5f);
            //
            //        if (ImGui::Combo("First skybox", &SelectedSkyboxFirstID, names.data(), Loader::sLoadedSkyboxes->size()))
            //        {
            //            Renderer::sSkyboxFirst = Loader::sLoadedSkyboxes->at(SelectedSkyboxNameFirst);
            //        }
            //
            //        if (ImGui::Combo("Second skybox", &SelectedSkyboxSecondID, names.data(), Loader::sLoadedSkyboxes->size()))
            //        {
            //            Renderer::sSkyboxSecond = Loader::sLoadedSkyboxes->at(SelectedSkyboxNameSecond);
            //        }
            //    }
            //    ImGui::EndChild();
            //}
            //ImGui::End();
		}

    };
}