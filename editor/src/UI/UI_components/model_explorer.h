#pragma once

#include "engine.h"

#include "imgui.h"
#include "file_dialog.h"
#include "Viewport/viewport.h"

#include <algorithm>


namespace Bubble
{
	class ModelExplorer
	{
		Ref<Model> SelectedModel = nullptr;

		// Draw selected model
		ThirdPersonCamera Camera;
		Viewport Viewport;
		Ref<Shader> Shader;
		Light Light;

	private:
		void DrawSelectedModel();

	public:
		ModelExplorer();
		void Draw(bool* is_open, DeltaTime dt);
	};

}