
#include "user_interface.h"


namespace Bubble
{
	void UI::Draw(DeltaTime dt)
	{
		mArgs.mImGuiControll->Begin();

		// MenuBar
		mArgs.mImGuiControll->BeginMenuBar();
		DrawMenuBar();
		mArgs.mImGuiControll->EndMenuBar();

		// Main UI
		DrawMainviewport(*mArgs.mViewport);
		mModelExplorer.Draw(&mIsOpenModelExplorer, dt);
		mSceneExplorer.Draw(&mIsOpenSceneExplorer, &mIsOpenEntityProperties, mArgs.mScene);

		// Temp
		ImGui::Begin("Info");
		{
			ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
		ImGui::End();

		// DemoWindow
		ImGui::ShowDemoWindow();

		mArgs.mImGuiControll->End();
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
						OpenProject(path, mArgs.mScene);
					}
					catch (const std::exception& e)
					{
						LOG_ERROR(e.what());
					}
				}

				if (ImGui::MenuItem("Save"))
				{
					SaveProject("../../../../scene_test.json", mArgs.mScene);
				}

				ImGui::EndMenu();
			}

			// ======================= Options =========================
			if (ImGui::BeginMenu("Options"))
			{
				// Scene camera
				if (ImGui::BeginMenu("Camera"))
				{
					SceneCameraOptions(mArgs.mCamera);
					ImGui::EndMenu();
				}

				// Rendering type
				if (ImGui::BeginMenu("Rendering"))
				{
					// Wireframe
					ImGui::Checkbox("Wireframe", (bool*)&mWireframeOption);
					Renderer::Wareframe(mWireframeOption);

					// BoundingBox
					ImGui::Checkbox("BoundingBox", (bool*)&mBoundingBoxOption);

					
					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}

			// ======================== View ============================
			if (ImGui::BeginMenu("View"))
			{
				ImGui::MenuItem("Scene explorer", "", &mIsOpenSceneExplorer);
				ImGui::MenuItem("Entity properties", "", &mIsOpenEntityProperties);
				ImGui::MenuItem("Model explorer", "", &mIsOpenModelExplorer);
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
	}

}
