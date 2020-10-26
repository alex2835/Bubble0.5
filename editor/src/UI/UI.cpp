
#include "UI.h"


namespace Bubble
{
	void UI::Draw(DeltaTime dt)
	{
		Args.ImGuiControll->Begin();

		// MenuBar
		Args.ImGuiControll->BeginMenuBar();
		DrawMenuBar();
		Args.ImGuiControll->EndMenuBar();

		// Main UI
		DrawMainviewport(*Args.MainViewport);
		ModelExplorerPanel.Draw(&IsOpenModelExplorer, dt);
		SceneExplorerPanel.Draw(&IsOpenSceneExplorer, &IsOpenEntityProperties, Args.ActiveScene);

		// Temp
		ImGui::Begin("Info");
		{
			ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
		ImGui::End();

		// DemoWindow
		ImGui::ShowDemoWindow();

		Args.ImGuiControll->End();
	}


	void UI::DrawMenuBar()
	{
		if (ImGui::BeginMenuBar())
		{
			// ========================= File =============================
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open"))
				{
					try
					{
						std::string path = OpenFileDialog("json");
						OpenProject(path, Args.ActiveScene);
					}
					catch (const std::exception& e)
					{
						LOG_ERROR(e.what());
					}
				}

				if (ImGui::MenuItem("Save"))
				{
					SaveProject("../../../../scene_test.json", Args.ActiveScene);
				}

				ImGui::EndMenu();
			}

			// ======================= Options =========================
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

			// ======================== View ============================
			if (ImGui::BeginMenu("View"))
			{
				ImGui::MenuItem("Scene explorer", "", &IsOpenSceneExplorer);
				ImGui::MenuItem("Entity properties", "", &IsOpenEntityProperties);
				ImGui::MenuItem("Model explorer", "", &IsOpenModelExplorer);
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
	}

}
