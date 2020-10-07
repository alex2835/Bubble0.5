
#include "editor_layer.h"


namespace Bubble
{

	EditorLayer::EditorLayer()
		: SceneCamera(glm::vec3(0.0f, 5.0f, 0.0f))
	{}

	void EditorLayer::OnAttach()
	{
        ImGuiControll.OnAttach();

        // Temp: test viewport
		ViewportArray.Push(Viewport(800, 800));

		// Temp: setup mesh
		m_Lights.push_back(Light::CreateSpotLight());
		m_Lights.push_back(Light::CreateDirLight(glm::vec3(0.1f, -1.0f, -1.0f)));
		m_Lights.push_back(Light::CreatePointLight(glm::vec3(3.0f, 5.0f, 0.0f)));

		ActiveScene = CreateRef<Scene>();

		glm::mat4 model(1.0f);
		model = glm::scale(model, glm::vec3(0.7f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));

		Entities.push_back(ActiveScene->CreateEntity("nanosuit")
			.AddComponent<Ref<Model>>(ModelLoader::StaticModel("resources/crysis/nanosuit.obj"))
			.AddComponent<TransformComponent>(model));

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f));
		model = glm::translate(model, glm::vec3(0.0f, -7.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));

		Entities.push_back(ActiveScene->CreateEntity("grass")
			.AddComponent<Ref<Model>>(ModelLoader::StaticModel("resources/grass_plane/grass_plane.obj"))
			.AddComponent<TransformComponent>(model));

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(10.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));

		Entities.push_back(ActiveScene->CreateEntity("tree")
			.AddComponent<Ref<Model>>(ModelLoader::StaticModel("resources/Tree/Tree.obj"))
			.AddComponent<TransformComponent>(model));

		m_ShaderPhong = Shader::Open("resources/shaders/phong.glsl");

		// Temp: skybox
		m_Skybox = CreateRef<Skybox>("resources/skybox/skybox1.jpg");
		m_ShaderSkybox = Shader::Open("resources/shaders/skybox.glsl");

		// Temp: Try to simplify mesh
	}


	void EditorLayer::OnDetach()
	{
        ImGuiControll.OnDetach();
	}
	

	void EditorLayer::OnUpdate(DeltaTime dt)
	{
		// Set args for UI
		UserInterface.Args = { &Models, &SceneCamera, &DrawTypeOption, ActiveScene.get() };

		// ImGui Scope
		ImGuiControll.Begin();

		// MenuBar
		ImGuiControll.BeginMenuBar();
		DrawMenuBar();
		ImGuiControll.EndMenuBar();

		// User Interface
		UserInterface.Draw();


        // Temp: Veiwports control
		ViewportArray.RemoveNotActiveViewports();
		
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		for (int i = 0; i < ViewportArray.Size(); i++)
		{
			ImGui::Begin(ViewportArray[i].GetName().c_str(), (bool*)&ViewportArray.IsOpen(i));

			ImVec2 imgui_viewport_size = ImGui::GetContentRegionAvail();
			glm::vec2 viewport_size = ViewportArray[i].Size();

			if (viewport_size != *(glm::vec2*) & imgui_viewport_size) {
				ViewportArray[i].Resize({ imgui_viewport_size.x, imgui_viewport_size.y });
			}

			uint32_t textureId = ViewportArray[i].GetFramebuffer().GetColorAttachmentRendererID();

			ImGui::Image((void*)textureId, ImVec2{ (float)ViewportArray[i].Size().x, (float)ViewportArray[i].Size().y }, ImVec2(1, 1), ImVec2(0, 0));
			ImGui::End();
		}
		ImGui::PopStyleVar();


		// Temp
		ImGui::Begin("Global light");
			ImGui::SliderFloat3("Direction", (float*)&m_Lights[1].Direction, -1.0f, 1.0f);
			ImGui::SliderFloat("Brightness", (float*)&m_Lights[1].Brightness, 0.0f, 1.0f);
			ImGui::ColorEdit3("Color", (float*)&m_Lights[1].Color);
		ImGui::End();
		ImGui::Begin("Flashlight");
			ImGui::SliderFloat("Distance", (float*)&m_Lights[0].Distance, 0.0f, 1.0f);
			ImGui::SliderFloat("Cutoff", (float*)&m_Lights[0].CutOff, 0.0f, 20.0f);
			ImGui::SliderFloat("OuterCutoff", (float*)&m_Lights[0].OuterCutOff, 0.0f, 20.0f);
			ImGui::ColorEdit3("Color", (float*)&m_Lights[0].Color);
			ImGui::SliderFloat("Brightness", &m_Lights[0].Brightness, 0.0f, 1.0f);
		ImGui::End();
		ImGui::Begin("PointLight");
			ImGui::SliderFloat("Distance", (float*)&m_Lights[2].Distance, 0.0f, 1.0f);
			ImGui::ColorEdit3("Color", (float*)&m_Lights[2].Color);
			ImGui::SliderFloat("Brightness", &m_Lights[2].Brightness, 0.0f, 1.0f);
		ImGui::End();

		ImGui::Begin("Info");
			ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		// DemoWindow
		ImGui::ShowDemoWindow();

        ImGuiControll.End();


		// ActiveScene update
		ActiveScene->OnUpdate(dt);

		// ActiveScene camera update
		SceneCamera.OnUpdate(dt);

		Renderer::SetViewport(ViewportArray[0].GetFramebuffer());
		Renderer::ClearDepth();

		m_Lights[0].Position = SceneCamera.m_Camera.Position;
		m_Lights[0].Direction = SceneCamera.m_Camera.Front;
		m_Lights[0].SetDistance();
		m_Lights[2].SetDistance();

		// Temp: Draw test mesh
		glm::ivec2 window_size = ViewportArray[0].Size();
		glm::mat4 projection = SceneCamera.GetPprojectionMat(window_size.x, window_size.y);
		glm::mat4 view = SceneCamera.GetLookatMat();
		
		m_Lights.ApplyLights(m_ShaderPhong);
		m_ShaderPhong->SetUniMat4("u_View", view);
		m_ShaderPhong->SetUniMat4("u_Projection", projection);

		auto ActiveScene_view = ActiveScene->GetView<Ref<Model>, TransformComponent>();

		for (auto entity : ActiveScene_view)
		{
			auto [model, transforms] = ActiveScene_view.get<Ref<Model>, TransformComponent>(entity);
			m_ShaderPhong->SetUniMat4("u_Model", transforms);
			Renderer::DrawModel(model, m_ShaderPhong, DrawTypeOption);
		}

		// Render skybox
		m_ShaderSkybox->SetUniMat4("u_Projection", projection);
		view = glm::rotate(view, glm::radians(Application::GetTime() * 0.5f), glm::vec3(0, 1, 0));
		m_ShaderSkybox->SetUniMat4("u_View", glm::mat3(view));
		m_ShaderSkybox->SetUni1f("u_Brightness", std::max(m_Lights[1].Brightness, 0.2f));
		Renderer::DrawSkybox(m_Skybox, m_ShaderSkybox);

	}

	void EditorLayer::OnEvent(SDL_Event& event)
	{
        ImGuiControll.OnEvent(event);

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
			Application::GetWindow()->Close();
		}
	}

	void EditorLayer::DrawMenuBar()
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open")) LOG_INFO("Open");
				if (ImGui::MenuItem("Save")) LOG_INFO("Save");

				ImGui::EndMenu();
			}

			UserInterface.DrawMenuOptions();

			ImGui::EndMenuBar();
		}
	}

}