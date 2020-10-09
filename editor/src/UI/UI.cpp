
#include "UI.h"


namespace Bubble
{
	void UI::Draw()
	{
		ModelExplorerPanel.Draw(&IsOpenModelExplorer);
		SceneExplorerPanel.Draw(&IsOpenSceneExplorer, &IsOpenEntityProperties, Args.ActiveScene);
	}


	void UI::DrawMenu()
	{
		if (ImGui::BeginMenu("Options"))
		{
			// Scene camera
			if (ImGui::BeginMenu("Camera"))
			{
				SceneCameraOptions(Args.Camera);
				ImGui::EndMenu();
			}

			// Rendering type
			if (ImGui::BeginMenu("Rendering"))
			{
				const char* const types[] = { "Lines", "Triangles" };
				ImGui::Combo("Type", (int*)&DrawTypeOption, types, 2);
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}


		if (ImGui::BeginMenu("View"))
		{
			ImGui::MenuItem("Scene explorer", "", &IsOpenSceneExplorer);
			ImGui::MenuItem("Entity properties", "", &IsOpenEntityProperties);
			ImGui::MenuItem("Model explorer", "", &IsOpenModelExplorer);
			ImGui::EndMenu();
		}

	}



}
