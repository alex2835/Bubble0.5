#pragma once

#include "bubble.h"
#include "ui_module.h"

namespace Bubble
{
	struct ScenePanel : UIModule
	{
		// Skybox
        int SelectedSkyboxFirstID  = 0;
        int SelectedSkyboxSecondID = 0;

        // Skysphere
        int SelectedSkyphereID = 0;

        inline ScenePanel()
            : UIModule("Scene panel")
        {}

		inline void Draw(UIArgs args, DeltaTime dt) override
		{
            ImGui::Begin(mName.c_str(), &mIsOpen);
            {
                ImVec2 window_size = ImGui::GetContentRegionAvail();

                // Background
                const char* sky_type_string = "Color\0Skybox\0Skysphere\0";

                ImGui::Combo("SkyType", (int*)&args.mRenderer->mSceneState.mBackgroundType, sky_type_string, 3);
                switch (args.mRenderer->mSceneState.mBackgroundType)
                {
                    case BackgroundType::COLOR:
                        ImGui::BeginChild("Active Color", ImVec2(0, 35), true);
                        ImGui::ColorEdit4("Background color", (float*)&args.mRenderer->mSceneState.mClearColor);
                        ImGui::EndChild();
                        break;
                    case BackgroundType::SKYBOX:
                        DrawSkyboxPanel(args);
                        break;
                    case BackgroundType::SKYSPHERE:
                        DrawSkyspherePanel(args);
                        break;
                }
                // ...
            }
            ImGui::End();
		}


    private:
        inline void DrawSkyboxPanel(UIArgs args)
        {
            RendererSceneState& scene_state = args.mRenderer->mSceneState;
            Loader& loader = *args.mLoader;

            // Load first skybox automatically
            if ((!scene_state.mSkyboxFirst ||
                !scene_state.mSkyboxSecond) &&
                args.mLoader->mLoadedSkyboxes.size())
            {
                for (const auto& [path, skybox] : args.mLoader->mLoadedSkyboxes)
                {
                    scene_state.mSkyboxFirst = skybox;
                    scene_state.mSkyboxSecond = skybox;
                }
            }

            // Skybox info
            std::string names;
            for (const auto& [path, skybox] : args.mLoader->mLoadedSkyboxes)
            {
                size_t start_pos = path.find_last_of("/") + 1;
                size_t end_pos   = path.find_last_of(".");
                std::string name = path.substr(start_pos, end_pos - start_pos);
                names += name + '\0';
            }
            
            ImGui::BeginChild("Active skyboxes", ImVec2(0, 130), true);
            {
                ImGui::SliderFloat("Brightness",   &scene_state.mSkyboxBrightness, 0.0f, 3.0f);
                ImGui::SliderFloat("Blend factor", &scene_state.mSkyboxBlendFactor, 0.0f, 1.0f);
                ImGui::SliderFloat("Rotation speed", &scene_state.mSkyboxRotationSpeed, 0.0001f, 0.5f);

                if (ImGui::Combo("First skybox", &SelectedSkyboxFirstID, names.data(), args.mLoader->mLoadedSkyboxes.size()))
                {
                    int i = 0;
                    for (const auto& [path, skybox] : args.mLoader->mLoadedSkyboxes)
                    {
                        if (i == SelectedSkyboxFirstID)
                            scene_state.mSkyboxFirst = skybox;
                        i++;
                    }
                }
                if (ImGui::Combo("Second skybox", &SelectedSkyboxSecondID, names.data(), args.mLoader->mLoadedSkyboxes.size()))
                {
                    int i = 0;
                    for (const auto& [path, skybox] : args.mLoader->mLoadedSkyboxes)
                    {
                        if (i == SelectedSkyboxSecondID)
                            scene_state.mSkyboxSecond = skybox;
                        i++;
                    }
                }

            }
            ImGui::EndChild();

        }

        inline void DrawSkyspherePanel(UIArgs args)
        {
            RendererSceneState& scene_state = args.mRenderer->mSceneState;
            Loader& loader = *args.mLoader;

            // Load first skysphere automatically
            if (!scene_state.mSkysphereTexture &&
                args.mLoader->mLoadedSkyspheres.size())
            {
                for (const auto& [path, skysphere_texture] : args.mLoader->mLoadedSkyspheres)
                    scene_state.mSkysphereTexture = skysphere_texture;
            }

            // Skysphere info
            std::string names;
            for (const auto& [path, skybox] : args.mLoader->mLoadedSkyspheres)
            {
                size_t start_pos = path.find_last_of("/") + 1;
                size_t end_pos = path.find_last_of(".");
                std::string name = path.substr(start_pos, end_pos - start_pos);
                names += name + '\0';
            }

            ImGui::BeginChild("Active Skysphere", ImVec2(0, 90), true);
            {
                auto& sphere_mesh = args.mRenderer->mStorage.mSphere->mMeshes[0];
                ImGui::SliderFloat("Brightness",     &scene_state.mSkyboxBrightness, 0.0f, 3.0f);
                ImGui::SliderFloat("Rotation speed", &scene_state.mSkyboxRotationSpeed, 0.0001f, 0.5f);

                if (ImGui::Combo("Skysphere", &SelectedSkyphereID, names.data(), args.mLoader->mLoadedSkyspheres.size()))
                {
                    int i = 0;
                    for (const auto& [path, skyphere_texture] : args.mLoader->mLoadedSkyspheres)
                    {
                        if (i == SelectedSkyphereID)
                            scene_state.mSkysphereTexture = skyphere_texture;
                        i++;
                    }
                }
            }
            ImGui::EndChild();
        }

    };
}