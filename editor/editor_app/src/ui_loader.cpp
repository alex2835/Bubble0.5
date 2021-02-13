
#include "ui_loader.h"
#include "serialization.h"

namespace Bubble
{
	UILoader::UILoader(Window* window)
        : mImGuiControl(window),
		  mUIDLL("../editor_ui/BubbleEditorUI")
    {
        mImGuiControl.OnAttach();
		mUIDLL.Call<void(ImGuiContext*)>("OnInit", mImGuiControl.mContext);
    }

	UILoader::~UILoader()
	{
		mImGuiControl.OnDetach();
	}

	void UILoader::OnUpdate(DeltaTime dt)
	{
		mImGuiControl.Begin();

		mImGuiControl.BeginMenuBar();
		mUIDLL.Call<void()>("OnMenuDraw");
		mImGuiControl.EndMenuBar();

		mUIDLL.Call<void(DeltaTime, UIArgs)>("OnDraw", dt, mArgs);
		mImGuiControl.End();
		
		// OnUpdate is called out of imgui scope
        mUIDLL.Call<void(DeltaTime)>("OnUpdate", dt);

		if (mUIDLL.CheckForUpdate())
		{
            mUIDLL.Call<void(ImGuiContext*)>("OnInit", mImGuiControl.mContext);
		}
	}

    void UILoader::OnEvent(SDL_Event& event)
    {
        mImGuiControl.OnEvent(event);
    }

	void UILoader::DrawMenuBar()
	{
		//if (ImGui::BeginMenuBar())
		//{
		//	// ========================= File =============================
		//	if (ImGui::BeginMenu("File"))
		//	{
		//		if (ImGui::MenuItem("Open"))
		//		{
		//			try
		//			{
		//				std::string path = OpenFileDialog("json");
		//				OpenProject(path, mArgs.mScene, this);
		//			}
		//			catch (const std::exception& e)
		//			{
		//				LOG_ERROR(e.what());
		//			}
		//		}
		//
		//		if (ImGui::MenuItem("Save"))
		//		{
		//			SaveProject("../../../../scene_test.json", mArgs.mScene, this);
		//		}
		//
		//		ImGui::EndMenu();
		//	}
		//
		//	// ======================= Options =========================
		//	if (ImGui::BeginMenu("Options"))
		//	{
		//		// Scene camera
		//		if (ImGui::BeginMenu("Camera"))
		//		{
		//			SceneCameraOptions(mArgs.mSceneCamera);
		//			ImGui::EndMenu();
		//		}
		//
		//		// Rendering type
		//		if (ImGui::BeginMenu("Rendering"))
		//		{
		//			// Wireframe
		//			ImGui::Checkbox("Wireframe", (bool*)&mWireframeOption);
		//			Renderer::Wareframe(mWireframeOption);
		//
		//			// BoundingBox
		//			ImGui::Checkbox("BoundingBox", (bool*)&mBoundingBoxOption);
		//
		//			
		//			ImGui::EndMenu();
		//		}
		//
		//		ImGui::EndMenu();
		//	}
		//
		//	// ======================== View ============================
		//	if (ImGui::BeginMenu("View"))
		//	{
		//		ImGui::MenuItem("Scene explorer", "", &mEntityExplorer->mIsOpen);
		//		//ImGui::MenuItem("Entity properties", "", &mIsOpenEntityProperties);
		//		ImGui::MenuItem("Model explorer", "", &mModelExploerer->mIsOpen);
		//		ImGui::MenuItem("Skybox explorer", "", &mSkyboxExplorer->mIsOpen);
		//		ImGui::EndMenu();
		//	}
		//
		//	ImGui::EndMenuBar();
		//}
	}

}
