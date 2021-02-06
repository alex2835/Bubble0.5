
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
				
				for (const auto& [path, skybox] : SkyboxLoader::sLoadedSkyboxes)
				{
					size_t pos = path.find_last_of("/") + 1;
					std::string name = path.substr(pos);
					mNames += name + '\0';
				}

				// Skyboxes
				ImGui::BeginChild("Active skyboxes", ImVec2(0, window_size.y * 0.2f), true);
				{
					ImGui::SliderFloat("Brightness", &Renderer::sSkyboxBrightness, 0.0f, 1.0f);
					ImGui::SliderFloat("Blend factor", &Renderer::sSkyboxBlendFactor, 0.0f, 1.0f);
					ImGui::SliderFloat("Rotation", &Renderer::sSkyboxRotationSpeed, 0.0001f, 0.5f);

					if (ImGui::Combo("First skybox", &nSelectedFirts, mNames.data(), SkyboxLoader::sLoadedSkyboxes.size()))
					{
						Renderer::sSkyboxFirst = SkyboxLoader::sLoadedSkyboxes[nSelectedFirts].second;
					}

					if (ImGui::Combo("Second skybox", &nSelectedSecond, mNames.data(), SkyboxLoader::sLoadedSkyboxes.size()))
					{
						Renderer::sSkyboxSecond = SkyboxLoader::sLoadedSkyboxes[nSelectedSecond].second;
					}
				}
				ImGui::EndChild();
				mNames.clear();
			}
			ImGui::End();
		}
	}

}