
#include "editor_layer.h"


namespace Bubble
{
	EditorLayer::EditorLayer()
		: mSceneCamera(glm::vec3(0.0f, 5.0f, 0.0f)),
		  mViewport(800, 800)
	{}

	void EditorLayer::OnAttach()
	{
        mImGuiControll.OnAttach();
	
		// Temp: load scene
		OpenProject("../../../../scene_test.json", &mScene);

		// Temp: skybox
		mActiveSkybox = SkyboxLoader::Load("resources/skybox/skybox1.jpg");
		mSkyboxShader = ShaderLoader::Load("resources/shaders/skybox.glsl");
		
		mPhongShader = ShaderLoader::Load("resources/shaders/phong.glsl");
		
		BufferLayout layout{
			{ GLSLDataType::Int, "Type"},
			{ GLSLDataType::Float, "Brightness"},

			{ GLSLDataType::Float, "Constant"},
			{ GLSLDataType::Float, "Linear"},
			{ GLSLDataType::Float, "Quadratic"},

			{ GLSLDataType::Float, "CutOff"},
			{ GLSLDataType::Float, "OuterCutOff"},

			{ GLSLDataType::Float3, "Color"},
			{ GLSLDataType::Float3, "Direction"},
			{ GLSLDataType::Float3, "Position"},
		};

		UBOLights = UniformBuffer(1, layout, 5, 16);

		// Temp: Try to simplify mesh
 	}


	void EditorLayer::OnDetach()
	{
        mImGuiControll.OnDetach();
	}
	

	void EditorLayer::OnUpdate(DeltaTime dt)
	{
		// ====================== Draw gui ======================
		mUI.mArgs = { &mImGuiControll, &mSceneCamera, &mViewport, &mScene };
		mUI.Draw(dt);


		// ====================== Update ======================
		mSceneCamera.OnUpdate(dt);

		for (Viewport* viewport : EditorViewports)
		{
			if (viewport->NewSize != viewport->GetSize())
			{
				viewport->Resize(viewport->NewSize);
			}
		}


		// ====================== Set uniform data ======================
		Renderer::SetViewport(mViewport);
		Renderer::SetCamera(mSceneCamera);

		// Temp
		static std::vector<Light> lights;
		lights.clear();

		mScene.Registry.view<LightComponent>().each(
			[&](auto& entity, LightComponent& lc)
			{
				lc.mLight.Update();
				lights.push_back(lc.mLight);
			}
		);

		int numLights = lights.size();
		UBOLights.SetData(lights.data(), sizeof(Light) * lights.size(), 16);
		UBOLights.SetData(&numLights, 4);


		// ====================== Rendering ======================
		mClearScreanOption |= mUI.mWireframeOption;

		if (mClearScreanOption)
		{
			Renderer::SetClearColor(glm::vec4(1.0f));
			Renderer::ClearColor();
		}
		Renderer::ClearDepth();


		// ====================== Draw scene ====================== 
		Renderer::DrawScene(mScene);


		// ====================== Draw editor sruff ======================
		Entity selected_entity = mUI.mSceneExplorer.SelectedEntity;

		// Highlight selected entity
		if (selected_entity)
		{
			draw_selected_model(selected_entity);
		}
		
		// Draw bounding boxes
		if (mUI.mBoundingBoxOption)
		{
			draw_scene_boundingbox(mScene);
		}

		// ========================= Draw skybox ========================= 
		glm::mat4 view = Renderer::ActiveCamera->GetLookatMat();

		float rotation = glm::radians(Timer::GetTime().GetSeconds() * 0.5f);
		view = glm::rotate(view, rotation, glm::vec3(0, 1, 0));
		view = glm::mat4(glm::mat3(view));

		Renderer::GetUBOPojectionView()[0].SetMat4("View", view);

		mSkyboxShader->SetUni1f("u_Brightness", 1.0f);
		Renderer::DrawSkybox(mActiveSkybox, mSkyboxShader);


		// Quit closure
		if (Input::IsKeyClick(SDLK_LALT) && Input::IsKeyClick(SDLK_F4))
		{
			Application::GetWindow()->Close();
		}
	}

	void EditorLayer::OnEvent(SDL_Event& event)
	{
        mImGuiControll.OnEvent(event);
	}

}