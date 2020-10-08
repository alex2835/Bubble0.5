
#include "model_explorer.h"


namespace Bubble
{


	void ModelExplorer::Draw(bool* is_open)
	{
		if (!*is_open) return;

		ImGui::Begin("Models explorer", is_open);


		for (auto name_model : ModelLoader::LoadedModels)
		{
			size_t pos = name_model.first.find_last_of("/") + 1;
			std::string name = name_model.first.substr(pos);
			
			ImGui::Selectable(name.c_str());

			if (ImGui::IsItemClicked())
			{
				SelectedModel = &name_model.second;
			}
		}

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
			SelectedModel = nullptr;
		}

		ImGui::End();
	}

}