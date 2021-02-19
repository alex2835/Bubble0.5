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
            RendererSceneStage& scene_stage = args.mRenderer->mSceneStage;
            Loader& loader = *args.mLoader;

            ImGui::Begin(mName.c_str(), &mIsOpen);
            {
                // ====================== Skyboxes ====================== 
                std::string names;
                for (const auto& [path, skybox] : args.mLoader->mLoadedSkyboxes)
                {
                    size_t start_pos = path.find_last_of("/") + 1;
                    size_t end_pos   = path.find_last_of(".");
                    std::string name = path.substr(start_pos, end_pos - start_pos);
                    names += name + '\0';
                }
            
                ImVec2 window_size = ImGui::GetContentRegionAvail();
                ImGui::BeginChild("Active skyboxes", ImVec2(0, window_size.y * 0.2f), true);
                {
                    ImGui::SliderFloat("Brightness",     &scene_stage.mSkyboxBrightness,    0.0f,    1.0f);
                    ImGui::SliderFloat("Blend factor",   &scene_stage.mSkyboxBlendFactor,   0.0f,    1.0f);
                    ImGui::SliderFloat("Rotation speed", &scene_stage.mSkyboxRotationSpeed, 0.0001f, 0.5f);
            
                    if (ImGui::Combo("First skybox", &SelectedSkyboxFirstID, names.data(), args.mLoader->mLoadedSkyboxes.size()))
                    {
                        int i = 0;
                        for (const auto& [path, skybox] : args.mLoader->mLoadedSkyboxes)
                        {
                            if (i == SelectedSkyboxFirstID)
                            {
                                SelectedSkyboxNameFirst  = path;
                                scene_stage.mSkyboxFirst = skybox;
                            }
                            i++;
                        }
                    }
                    if (ImGui::Combo("Second skybox", &SelectedSkyboxSecondID, names.data(), args.mLoader->mLoadedSkyboxes.size()))
                    {
                        int i = 0;
                        for (const auto& [path, skybox] : args.mLoader->mLoadedSkyboxes)
                        {
                            if (i == SelectedSkyboxSecondID)
                            {
                                SelectedSkyboxNameSecond  = path;
                                scene_stage.mSkyboxSecond = skybox;
                            }
                            i++;
                        }
                    }
                }
                ImGui::EndChild();

                // ====================== Something ======================
                // ... 
            }
            ImGui::End();
		}

    };
}