
#include "editor_layer.h"


namespace Bubble
{
    EditorLayer::EditorLayer()
		: m_SceneCamera(glm::vec3(0.0f, 5.0f, 0.0f))
	{}

	void EditorLayer::OnAttach()
	{
        m_ImGuiControll.OnAttach();

        // Temp: test viewport
		m_ViewportArray.Push(Viewport(800, 800));


		// Temp: setup mesh
		m_Lights.push_back(Light::CreateSpotLight());
		m_Lights.push_back(Light::CreateDirLight(glm::vec3(0.1f, -1.0f, -1.0f)));
		m_Lights.push_back(Light::CreatePointLight(glm::vec3(3.0f, 5.0f, 0.0f)));

		m_ShaderPhong = Shader::Open("resources/shaders/phong.glsl");
		m_NanoSuit = ModelLoader::StaticModel("resources/crysis/nanosuit.obj");
		m_GrassPlane = ModelLoader::StaticModel("resources/grass_plane/grass_plane.obj");
		m_Tree = ModelLoader::StaticModel("resources/Tree/Tree.obj");

		// Temp: skybox
		m_Skybox = CreateRef<Skybox>("resources/skybox/skybox1.jpg");
		m_ShaderSkybox = Shader::Open("resources/shaders/skybox.glsl");

		// Temp: Scene
		m_Scene = CreateRef<Scene>();
		m_Entity = m_Scene->CreateEntity("TestEntity");


		// Temp: Try to simplify mesh


	}


	void EditorLayer::OnDetach()
	{
        m_ImGuiControll.OnDetach();
	}
	

	void EditorLayer::OnUpdate(DeltaTime dt)
	{
		m_ImGuiControll.Begin();

        // Temp: Veiwports control
		m_ViewportArray.RemoveNotActiveViewports();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

		for (int i = 0; i < m_ViewportArray.Size(); i++)
		{
			ImGui::Begin(m_ViewportArray[i].GetName().c_str(), (bool*)&m_ViewportArray.IsOpen(i));

			ImVec2 imgui_viewport_size = ImGui::GetContentRegionAvail();
			glm::vec2 viewport_size = m_ViewportArray[i].Size();

			if (viewport_size != *(glm::vec2*) & imgui_viewport_size) {
				m_ViewportArray[i].Resize({ imgui_viewport_size.x, imgui_viewport_size.y });
			}

			uint32_t textureId = m_ViewportArray[i].GetFramebuffer().GetColorAttachmentRendererID();

			ImGui::Image((void*)textureId, ImVec2{ (float)m_ViewportArray[i].Size().x, (float)m_ViewportArray[i].Size().y }, ImVec2(1, 1), ImVec2(0, 0));
			ImGui::End();
		}
		ImGui::PopStyleVar();

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

		ImGui::Begin("Test file dilog");
		bool open = ImGui::Button("Open", { 100, 50 });
		if (open)
		{
			nfdchar_t* outPath = NULL;
			nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath);

			if (result == NFD_OKAY) {
				puts("Success!");
				puts(outPath);
				free(outPath);
			}
			else if (result == NFD_CANCEL) {
				puts("User pressed cancel.");
			}
			else {
				printf("Error: %s\n", NFD_GetError());
			}
		}
		ImGui::End();


        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		ImGui::ShowDemoWindow();
        m_ImGuiControll.End();


		// Scene update
		m_Scene->OnUpdate(dt);

		// Scene camera update
		m_SceneCamera.OnUpdate(dt);

		Renderer::SetViewport(m_ViewportArray[0].GetFramebuffer());
		Renderer::ClearDepth();

		m_Lights[0].Position = m_SceneCamera.m_Camera.Position;
		m_Lights[0].Direction = m_SceneCamera.m_Camera.Front;
		m_Lights[0].SetDistance();
		m_Lights[2].SetDistance();

		// Temp: Draw test mesh
		glm::ivec2 window_size = m_ViewportArray[0].Size();
		glm::mat4 projection = m_SceneCamera.GetPprojectionMat(window_size.x, window_size.y);
		glm::mat4 view = m_SceneCamera.GetLookatMat();
		
		m_Lights.ApplyLights(m_ShaderPhong);
		m_ShaderPhong->SetUniMat4("u_View", view);
		m_ShaderPhong->SetUniMat4("u_Projection", projection);

		glm::mat4 model(1.0f);
		model = glm::scale(model, glm::vec3(0.7f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
		m_ShaderPhong->SetUniMat4("u_Model", model);
		Renderer::DrawModel(m_NanoSuit, m_ShaderPhong);
		
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(10.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		m_ShaderPhong->SetUniMat4("u_Model", model);
		Renderer::DrawModel(m_Tree, m_ShaderPhong);
		
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f));
		model = glm::translate(model, glm::vec3(0.0f, -7.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
		m_ShaderPhong->SetUniMat4("u_Model", model);
		Renderer::DrawModel(m_GrassPlane, m_ShaderPhong);

		// Render skybox
		m_ShaderSkybox->SetUniMat4("u_Projection", projection);
		view = glm::rotate(view, glm::radians(Application::GetTime() * 0.5f), glm::vec3(0, 1, 0));
		m_ShaderSkybox->SetUniMat4("u_View", glm::mat3(view));
		m_ShaderSkybox->SetUni1f("u_Brightness", std::max(m_Lights[1].Brightness, 0.2f));
		Renderer::DrawSkybox(m_Skybox, m_ShaderSkybox);

	}

	void EditorLayer::OnEvent(SDL_Event& event)
	{
        m_ImGuiControll.OnEvent(event);

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
			Application::GetWindow()->Close();
		}
	}

}