
#include "UI.h"


namespace Bubble
{
	void UI::Draw(UIArgs args)
	{
		model_loader_UI(&ModelLoader, args.Models);
		
	}


	void UI::DrawMenuOptions()
	{
		if (ImGui::BeginMenu("Options"))
		{
			// Scene camera
			if (ImGui::BeginMenu("Camera"))
			{
				scene_camera_options(Args.Camera);
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
