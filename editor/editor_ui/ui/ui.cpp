
#include "ui.h"

namespace Bubble
{
	Scope<std::vector<Ref<UIModule>>> UI::sModules;

	UI::UI()
    {
		sModules = CreateScope<std::vector<Ref<UIModule>>>();
		// Create ui modules
		mMainViewport   = AddModule<MainViewport>();
		mModelExploerer = AddModule<ModelExplorer>();
		mEntityExplorer = AddModule<EntityExplorer>();
		mSkyboxExplorer = AddModule<SkyboxExplorer>();
		mScenePanel     = AddModule<ScenePanel>();
    }

	void UI::AddModule(const Ref<UIModule>& ui_module)
	{
		auto iterator = std::find_if(sModules->begin(), sModules->end(),
			[&ui_module](const auto& module_elem) { return module_elem->mName == ui_module->mName; });
		
		if (iterator == sModules->end())
			sModules->push_back(ui_module);
		else
			BUBBLE_ASSERT(false, "Module with name {} already exist", ui_module->mName);
	}

	void UI::RemoveModule(const std::string& name)
	{
		auto iterator = std::find_if(sModules->begin(), sModules->end(),
			[&name](const auto& ui_module) { return ui_module->mName == name; });
		sModules->erase(iterator);
	}

	UI::~UI()
	{}

	void UI::OnDraw(DeltaTime dt)
	{
        for (int i = 0; i < sModules->size(); i++)
        {
            auto& ui_module = sModules->at(i);
            if (ui_module->IsOpen())
                ui_module->Draw(mArgs, dt);
        }

        // Temp frame rate info
        ImGui::Begin("Info");
        {
            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        ImGui::End();
	}

	void UI::OnUpdate(DeltaTime dt)
	{
        for (int i = 0; i < sModules->size(); i++)
            sModules->at(i)->OnUpdate(mArgs, dt);
	}

    void UI::OnEvent(SDL_Event& event)
    {
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
					//ProjectDeserialization("../../../../../scene_test.json", *mArgs.mLoader, *mArgs.mRenderer, *mArgs.mScene);
					//try
					//{
					//	std::string path = OpenFileDialog("json");
					//	ProjectDeserialization(path, *mArgs.mLoader, *mArgs.mRenderer, *mArgs.mScene);
					//}
					//catch (const std::exception& e)
					//{
					//	LOG_ERROR(e.what());
					//}
				}
				
				if (ImGui::MenuItem("Save"))
				{
					//ProjectSerialization("../../../../../scene_test.json", *mArgs.mLoader, *mArgs.mRenderer, *mArgs.mScene);
				}

				ImGui::EndMenu();
			}

			// ======================= Options =========================
			if (ImGui::BeginMenu("Options"))
			{
				// Scene camera
				if (ImGui::BeginMenu("Camera"))
				{
					//SceneCameraOptions(mArgs.mSceneCamera);
					ImGui::EndMenu();
				}

				// Rendering type
				if (ImGui::BeginMenu("Rendering"))
				{
					// Wireframe
					//ImGui::Checkbox("Wireframe", (bool*)&mWireframeOption);
					//Renderer::Wareframe(mWireframeOption);
					//
					//// BoundingBox
					//ImGui::Checkbox("BoundingBox", (bool*)&mBoundingBoxOption);
					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}

			// ======================== View ========================
			if (ImGui::BeginMenu("View"))
			{
				ImGui::MenuItem("Scene explorer",  "", &mEntityExplorer->mIsOpen);
				ImGui::MenuItem("Model explorer",  "", &mModelExploerer->mIsOpen);
				ImGui::MenuItem("Skybox explorer", "", &mSkyboxExplorer->mIsOpen);
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
	}

}
