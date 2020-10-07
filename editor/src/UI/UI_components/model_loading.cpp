
#include "model_loading.h"


namespace Bubble
{
	
	void ModelLoaderUI(bool* is_open, std::vector<Ref<Model>>* models)
	{
		if (!*is_open) return;

		ImGui::Begin("Open model dialog", is_open);
		bool button_pressed = ImGui::Button("Open", { 100, 50 });
		
		if (button_pressed)
		{
			try {
				auto path = OpenFileDialog();
				models->push_back(ModelLoader::StaticModel(path));
			}
			catch (const std::exception& e) {
				LOG_ERROR(e.what());
			}
		}
		ImGui::End();
	}

}