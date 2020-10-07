
#include "model_loading.h"


namespace Bubble
{
	
	void model_loader_UI(bool* is_open, std::vector<Ref<Model>>* models)
	{
		static bool IsDialogOpen = true;

		ImGui::Begin("Open model dialog", is_open);
		bool button_pressed = ImGui::Button("Open", { 100, 50 });
		
		if (button_pressed)
		{
			auto path = OpenFileDialog();
			models->push_back(ModelLoader::StaticModel(path));
		}
		ImGui::End();
	}

}