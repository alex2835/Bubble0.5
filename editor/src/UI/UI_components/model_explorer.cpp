
#include "model_explorer.h"


namespace Bubble
{

	ModelExplorer::ModelExplorer()
		: Viewport(800, 600),
		  Shader(Shader::Open("resources/Shaders/phong.glsl")),
		  Light(Light::CreateDirLight())
	{}

	void ModelExplorer::DrawSelectedModel()
	{
		Light::ApplyLight(Light, Shader, 0);
		Shader->SetUni1i("nLights", 1);
		
		// Transforms
		glm::mat4 view = Camera.GetLookatMat();
		glm::mat4 projection = Camera.GetPprojectionMat(Viewport.GetWidth(), Viewport.GetHeight());
		
		Shader->SetUniMat4("u_View", view);
		Shader->SetUniMat4("u_Projection", projection);
		
		glm::mat4 model(1.0f);
		Shader->SetUniMat4("u_Model", model);
		 
		Renderer::SetViewport(Viewport);
		Renderer::SetClearColor(glm::vec4(0.4f));
		Renderer::Clear();
		
		Renderer::DrawModel(SelectedModel, Shader);
		
		Viewport.Unbind();
	}

	void ModelExplorer::Draw(bool* is_open, DeltaTime dt)
	{
		if (!*is_open) return;

		ImGui::Begin("Models explorer", is_open);
		{
			ImVec2 window_size = ImGui::GetContentRegionAvail();
			ImVec2 pos = ImGui::GetCursorScreenPos();

			//  ============ Model view =================
			if (SelectedModel) {
				DrawSelectedModel();
			}
			Viewport.Resize({ window_size.x, window_size.y * 0.6f });
			uint32_t textureId = Viewport.GetColorAttachmentRendererID();
			ImGui::GetWindowDrawList()->AddImage((void*)textureId, pos, ImVec2{ pos.x + window_size.x, pos.y + window_size.y * 0.7f }, ImVec2(1, 1), ImVec2(0, 0));

			ImGui::InvisibleButton("##dummy", ImVec2{ window_size.x + 1, window_size.y * 0.7f + 1});
			if (ImGui::IsItemActive() && ImGui::IsMouseDragging(0))
			{
				Camera.ProcessMouseMovementShift(Input::fGetMouseRelX(), -Input::fGetMouseRelY());
				Camera.UpdateCameraAngles(dt);
			}

			if (ImGui::IsWindowFocused())
			{
				Camera.Radius = std::max(Camera.Radius - Input::GetMouseWheelOffset() * 7, 10.0f);
				Camera.UpdateCameraAngles(dt);
			}

			// ================= Model list ====================
			ImGui::BeginChild("Models list", ImVec2(0, window_size.y * 0.22f), true);
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

			if (ImGui::Button("Load", {100, window_size.y * 0.05f}))
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