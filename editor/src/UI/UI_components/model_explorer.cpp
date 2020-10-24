
#include "model_explorer.h"


namespace Bubble
{

	ModelExplorer::ModelExplorer()
		: ActiveViewport(Framebuffer(FramebufferSpecification{ {1000, 600} })),
		  ActiveCamera(Camera(glm::vec3(0, 5, 20))),
		  Scale(1.0f)
	{}

	void ModelExplorer::DrawSelectedModel()
	{
		static Ref<Shader> shader = Shader::Open("resources/shaders/phong.glsl");
		static Light light = Light::CreateDirLight();
		Light::ApplyLight(light, shader, 0);
		shader->SetUni1i("nLights", 1);
		
		// Transforms
		glm::mat4 view = ActiveCamera.GetLookatMat();
		glm::mat4 projection = ActiveCamera.GetPprojectionMat(ActiveViewport.GetWidth(), ActiveViewport.GetHeight());
		
		shader->SetUniMat4("u_View", view);
		shader->SetUniMat4("u_Projection", projection);
		
		glm::mat4 model(1.0f);
		//modal = glm::scale()
		
		shader->SetUniMat4("u_Model", model);
		 
		Renderer::SetViewport(ActiveViewport);
		Renderer::SetClearColor(glm::vec4(1.0f));
		Renderer::Clear();
		
		Renderer::DrawModel(SelectedModel, shader);
		
		ActiveViewport.Unbind();
	}

	void ModelExplorer::Draw(bool* is_open)
	{
		if (!*is_open) return;

		ImGui::Begin("Models explorer", is_open);
		{
			ImVec2 viewport_size = ImGui::GetContentRegionAvail();
			ImVec2 pos = ImGui::GetCursorScreenPos();

			//  ============ Model view =================
			if (SelectedModel) {
				DrawSelectedModel();
			}
			uint32_t textureId = ActiveViewport.GetColorAttachmentRendererID();
			ImGui::GetWindowDrawList()->AddImage((void*)textureId, pos, ImVec2{ pos.x + viewport_size.x, pos.y + viewport_size.y * 0.6f }, ImVec2(1, 1), ImVec2(0, 0));

			ImGui::InvisibleButton("##dummy", ImVec2{ viewport_size.x, viewport_size.y * 0.6f });
			if (ImGui::IsItemActive() && ImGui::IsMouseDragging(0))
			{
				ActiveCamera.Yaw -= ImGui::GetIO().MouseDelta.x * 0.01f;
				ActiveCamera.Pitch -= ImGui::GetIO().MouseDelta.y * 0.01f;
				ActiveCamera.UpdateCameraVectors();
			}

			// ================= Model list ====================
			ImGui::BeginChild("Models list", ImVec2(0, viewport_size.y * 0.3f), true);
			{
				for (auto name_model : ModelLoader::LoadedModels)
				{
					size_t pos = name_model.first.find_last_of("/") + 1;
					std::string name = name_model.first.substr(pos);

					ImGui::Selectable(name.c_str());

					if (ImGui::IsItemClicked())
						SelectedModel = name_model.second;
				}

				if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
					SelectedModel = nullptr;
				}
			}
			ImGui::EndChild();

			if (ImGui::Button("Load", {100, viewport_size.y * 0.05f}))
			{
				try
				{
					std::string path = OpenFileDialog();
					ModelLoader::StaticModel(path);
				}
				catch (const std::exception& e)
				{
					LOG_ERROR(e.what());
				}
			}

		}
		ImGui::End();

	}

}