
#include "UI.h"


namespace Bubble
{
	void UI::Draw()
	{
		//ModelLoaderUI(&IsOpenModelLoader, Args.Models);

		ModelExplorerPanel.Draw(&IsOpenModelExplorer);

		EntityExplorerPanel.DrawEntitiesExplorer(&IsOpenSceneExplorer, &IsOpenEntityProperties, Args.ActiveScene);
	}


	void UI::DrawMenuOptions()
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
				ImGui::Combo("Type", (int*)Args.DrawTypeOption, types, 2);
				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}
	}



}
