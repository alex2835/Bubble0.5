
#include "main_viewport.h"


namespace Bubble
{
	void DrawMainviewport(Viewport& viewport)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");
		{
			ImVec2 imgui_viewport_size = ImGui::GetContentRegionAvail();
			glm::vec2 viewport_size = viewport.GetSize();

			uint32_t textureId = viewport.GetColorAttachmentRendererID();
			ImGui::Image((void*)textureId, ImVec2{ (float)viewport.GetWidth(), (float)viewport.GetHeight() }, ImVec2(1, 1), ImVec2(0, 0));

			viewport.NewSize = *(glm::vec2*)&imgui_viewport_size;
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}

}