#pragma once

#include "engine.h"
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
                const char* sky_type_string = "Color\0Skybox\0Skysphere";

                ImGui::Combo("SkyType", (int*)&args.mRenderer->mBackgroundType, sky_type_string, 3);
                switch (args.mRenderer->mBackgroundType)
                {
                    case BackgroundType::COLOR:
                        ImGui::ColorEdit4("Background color", (float*)&args.mRenderer->mSceneStage.mClearColor);
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
            RendererSceneStage& scene_stage = args.mRenderer->mSceneStage;
            Loader& loader = *args.mLoader;

            // Load first skybox automatically
            if ((!scene_stage.mSkyboxFirst ||
                !scene_stage.mSkyboxSecond) &&
                args.mLoader->mLoadedSkyboxes.size())
            {
                for (const auto& [path, skybox] : args.mLoader->mLoadedSkyboxes)
                {
                    scene_stage.mSkyboxFirst = skybox;
                    scene_stage.mSkyboxSecond = skybox;
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
                ImGui::SliderFloat("Brightness",   &scene_stage.mSkyboxBrightness, 0.0f, 1.0f);
                ImGui::SliderFloat("Blend factor", &scene_stage.mSkyboxBlendFactor, 0.0f, 1.0f);
                ImGui::SliderFloat("Rotation speed", &scene_stage.mSkyboxRotationSpeed, 0.0001f, 0.5f);

                if (ImGui::Combo("First skybox", &SelectedSkyboxFirstID, names.data(), args.mLoader->mLoadedSkyboxes.size()))
                {
                    int i = 0;
                    for (const auto& [path, skybox] : args.mLoader->mLoadedSkyboxes)
                    {
                        if (i == SelectedSkyboxFirstID)
                        {
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
                            scene_stage.mSkyboxSecond = skybox;
                        }
                        i++;
                    }
                }

            }
            ImGui::EndChild();

        }

        inline void DrawSkyspherePanel(UIArgs args)
        {
            RendererSceneStage& scene_stage = args.mRenderer->mSceneStage;
            Loader& loader = *args.mLoader;

            // Load first skysphere automatically
            if (!scene_stage.mSkysphereTexture &&
                args.mLoader->mLoadedSkypsheres.size())
            {
                for (const auto& [path, skysphere_texture] : args.mLoader->mLoadedSkypsheres)
                {
                    scene_stage.mSkysphereTexture = skysphere_texture;
                }
            }

            // Skysphere info
            std::string names;
            for (const auto& [path, skybox] : args.mLoader->mLoadedSkypsheres)
            {
                size_t start_pos = path.find_last_of("/") + 1;
                size_t end_pos = path.find_last_of(".");
                std::string name = path.substr(start_pos, end_pos - start_pos);
                names += name + '\0';
            }

            ImGui::BeginChild("Active skyboxes", ImVec2(0, 130), true);
            {
                auto& sphere_mesh = args.mRenderer->mStorage.mSphere->mMeshes[0];
                ImGui::SliderFloat("Brightness",     &sphere_mesh.mMaterial.mAmbientCoef, 0.0f, 3.0f);
                ImGui::SliderFloat("Rotation speed", &scene_stage.mSkyboxRotationSpeed, 0.0001f, 0.5f);

                if (ImGui::Combo("Skysphere", &SelectedSkyphereID, names.data(), args.mLoader->mLoadedSkypsheres.size()))
                {
                    int i = 0;
                    for (const auto& [path, skyphere_texture] : args.mLoader->mLoadedSkypsheres)
                    {
                        if (i == SelectedSkyphereID)
                        {
                            scene_stage.mSkysphereTexture = skyphere_texture;
                        }
                        i++;
                    }
                }
            }
            ImGui::EndChild();
        }

    };
}