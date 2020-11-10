
#include "scene_panel.h"


namespace Bubble
{

	void ScenePanel::Draw(bool* is_open)
	{
		if (*is_open)
		{
			ImGui::Begin("Scene panel");
			{
				ImVec2 window_size = ImGui::GetContentRegionAvail();
				
				for (const auto& [path, skybox] : SkyboxLoader::LoadedSkyboxes)
				{
					size_t pos = path.find_last_of("/") + 1;
					std::string name = path.substr(pos);
					mNames += name + '\0';
				}

				// Skyboxes
				ImGui::BeginChild("Active skyboxes", ImVec2(0, window_size.y * 0.2f), true);
				{
					ImGui::SliderFloat("Brightness", &Renderer::SkyboxBrightness, 0.0f, 1.0f);
					ImGui::SliderFloat("Blend factor", &Renderer::SkyboxBlendFactor, 0.0f, 1.0f);
					ImGui::SliderFloat("Rotation", &Renderer::SkyboxRotation, 0.0001f, 0.5f);

					if (ImGui::Combo("First skybox", &nSelectedFirts, mNames.data(), SkyboxLoader::LoadedSkyboxes.size()))
					{
						Renderer::SkyboxFirst = SkyboxLoader::LoadedSkyboxes[nSelectedFirts].second;
					}

					if (ImGui::Combo("Second skybox", &nSelectedSecond, mNames.data(), SkyboxLoader::LoadedSkyboxes.size()))
					{
						Renderer::SkyboxSecond = SkyboxLoader::LoadedSkyboxes[nSelectedSecond].second;
					}
				}
				ImGui::EndChild();
				mNames.clear();
			}
			ImGui::End();

		}
	}

}