
#include "model_explorer.h"


namespace Bubble
{
	ModelExplorer::ModelExplorer()
		: mViewport(800, 600),
		  mShader(ShaderLoader::Load("resources/shaders/phong.glsl")),
		  mLight(Light::CreateDirLight()),
		  mCamera(0)
	{}

	void ModelExplorer::DrawSelectedModel()
	{
		Light::ApplyLight(mLight, mShader, 0);
		mShader->SetUni1i("nLights", 1);
		
		// Transforms
		glm::mat4 model(1.0f);
		glm::mat4 view = mCamera.GetLookatMat();
		glm::mat4 projection = mCamera.GetPprojectionMat(mViewport.GetWidth(), mViewport.GetHeight());
		
		mShader->SetUniMat4("u_Model", model);
		mShader->SetUniMat4("u_View", view);
		mShader->SetUniMat4("u_Projection", projection);
		 
		Renderer::SetViewport(mViewport);
		Renderer::SetClearColor(glm::vec4(0.4f));
		Renderer::Clear();
		
		Renderer::DrawModel(mSelectedModel, mShader);
		
		mViewport.Unbind();
	}

	void ModelExplorer::Draw(bool* is_open, DeltaTime dt)
	{
		if (!*is_open) return;

		ImGui::Begin("Models explorer", is_open);
		{
			ImVec2 window_size = ImGui::GetContentRegionAvail();
			ImVec2 pos = ImGui::GetCursorScreenPos();

			//  ================= Model view =================
			if (mSelectedModel) {
				DrawSelectedModel();
			}
			
			// Draw viewport
			mViewport.Resize({ window_size.x, window_size.y * 0.6f });
			uint32_t textureId = mViewport.GetColorAttachmentRendererID();
			ImGui::GetWindowDrawList()->AddImage((void*)textureId, pos, ImVec2{ pos.x + window_size.x, pos.y + window_size.y * 0.7f }, ImVec2(1, 1), ImVec2(0, 0));

			// Invisible drag able area
			ImGui::InvisibleButton("##dummy", ImVec2{ window_size.x + 1, window_size.y * 0.7f + 1});
			if (ImGui::IsItemActive() && ImGui::IsMouseDragging(0))
			{
				// Moving by dragging
				mCamera.ProcessMouseMovementShift(Input::fGetMouseRelX(), -Input::fGetMouseRelY());
				mCamera.UpdateCameraAngles(dt);
			}

			// Change radius by mouse wheel moving
			if (ImGui::IsWindowFocused())
			{
				if (mSelectedModel)
				{
					float longest_edge = mSelectedModel->mBoundingBox.getLongestEdge();
					mCamera.Radius -= Input::GetMouseWheelOffset() * longest_edge / 5;
					mCamera.Radius = glm::clamp(mCamera.Radius, longest_edge, mCamera.Far);
					mCamera.UpdateCameraAngles(dt);
				}
			}

			// ==================== Model list ====================
			ImGui::BeginChild("Models list", ImVec2(0, window_size.y * 0.2f), true);
			{
				for (auto name_model : ModelLoader::LoadedModels)
				{
					size_t pos = name_model.first.find_last_of("/") + 1;
					std::string name = name_model.first.substr(pos);

					ImGui::Selectable(name.c_str());

					// Switch
					if (ImGui::IsItemClicked())
					{
						mSelectedModel = name_model.second;
						// Start camera params for this model
						mCamera.Center = mSelectedModel->mBoundingBox.getCenter();
						mCamera.Radius = mSelectedModel->mBoundingBox.getLongestEdge() * 1.5f;
						mCamera.UpdateCameraAngles(dt);
					}
				}
				
				if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
					mSelectedModel = nullptr;
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