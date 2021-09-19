#pragma once

#include "imgui.h"
#include "imgui_tools.h"
#include <string>
#include "bubble.h"

namespace Bubble
{
	inline void DrawImageWithText(const Ref<Texture2D>& texture,
								  const std::string& name,
								  ImVec2 size,
								  int items_in_row,
								  int item_num)
	{
		if (item_num % items_in_row)
			ImGui::SameLine();

		ImGui::BeginChild(item_num + 1, size + ImVec2(0, 50));
			ImGui::Image((void*)texture->GetRendererID(), size);
			ImGui::Text(name.c_str());
		ImGui::EndChild();
	}
}