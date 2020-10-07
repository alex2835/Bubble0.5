#pragma once

#include "file_dialog.h"
#include "imgui.h"
#include "model/model_loader.h"

namespace Bubble
{
	void ModelLoaderUI(bool* is_open, std::vector<Ref<Model>>* models);

}