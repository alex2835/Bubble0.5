
#include "ui.h"
#include "serialization/serialization.h"

namespace Bubble
{
	Scope<std::vector<Ref<UIModule>>> UI::sModules;

	UI::UI(Window* window)
        : mImGuiControl(window)
    {
        mImGuiControl.OnAttach();
		sModules = CreateScope<std::vector<Ref<UIModule>>>();

		// Create default ui modules
		mMainViewport   = AddModule<MainViewport>();
		mModelExploerer = AddModule<ModelExplorer>();
		mEntityExplorer = AddModule<EntityExplorer>();
		mSkyboxExplorer = AddModule<SkyboxExplorer>();
		mScenePanel     = AddModule<ScenePanel>();

    }

	int UI::AddModule(const Ref<UIModule>& ui_module)
	{
		auto iterator = std::ranges::find(*sModules, ui_module);
		if (iterator == sModules->end())
		{
			sModules->push_back(ui_module);
		}
		return sModules->back()->GetID();
	}

	void UI::RemoveModule(int module_id)
	{
		auto iterator = std::find_if(sModules->begin(), sModules->end(),
			[module_id](const auto& ui_module) { return ui_module->GetID() == module_id; });
		sModules->erase(iterator);
	}

	UI::~UI()
	{
		mImGuiControl.OnDetach();
	}

	void UI::OnUpdate(DeltaTime dt)
	{
		mImGuiControl.Begin();

		mImGuiControl.BeginMenuBar();
		DrawMenuBar();
		mImGuiControl.EndMenuBar();

		//for (int i = 0; i < sModules->size(); i++)
		//{
		//	auto& ui_module = sModules->at(i);
		//	if (!ui_module->IsOpen())
		//	{
		//		auto iterator = std::ranges::find(*sModules, ui_module);
		//		sModules->erase(iterator);
		//	}
		//}

		for (int i = 0; i < sModules->size(); i++)
		{
			auto& ui_module = sModules->at(i);
			if (ui_module->IsOpen())
			{
				ui_module->Draw(mArgs, dt);
			}
		}

        // Temp frame rate info
        ImGui::Begin("Info");
        {
            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        ImGui::End();
		
		mImGuiControl.End();

        for (int i = 0; i < sModules->size(); i++)
        {
            sModules->at(i)->OnUpdate(mArgs, dt);
        }
	}

    void UI::OnEvent(SDL_Event& event)
    {
        mImGuiControl.OnEvent(event);
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
						OpenProject(path, mArgs.mScene, this);
					}
					catch (const std::exception& e)
					{
						LOG_ERROR(e.what());
					}
				}

				if (ImGui::MenuItem("Save"))
				{
					SaveProject("../../../../scene_test.json", mArgs.mScene, this);
				}

				ImGui::EndMenu();
			}

			// ======================= Options =========================
			if (ImGui::BeginMenu("Options"))
			{
				// Scene camera
				if (ImGui::BeginMenu("Camera"))
				{
					SceneCameraOptions(mArgs.mSceneCamera);
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
				ImGui::MenuItem("Scene explorer", "", &mEntityExplorer->mIsOpen);
				//ImGui::MenuItem("Entity properties", "", &mIsOpenEntityProperties);
				ImGui::MenuItem("Model explorer", "", &mModelExploerer->mIsOpen);
				ImGui::MenuItem("Skybox explorer", "", &mSkyboxExplorer->mIsOpen);
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
	}

}
