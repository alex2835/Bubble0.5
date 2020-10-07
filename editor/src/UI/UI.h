#pragma once

#include "UI_components/model_loading.h"
#include "UI_components/camera_options.h"


namespace Bubble
{
	struct UIArgs
	{
		std::vector<Ref<Model>>* Models;
		SceneCameraController* Camera;
		// Rendering
		DrawType* DrawTypeOption;
	};

	class UI
	{
	public:
		UIArgs Args;

		bool ModelLoader = false;
		bool CameraOptions = false;

		void Draw(UIArgs args);
		void DrawMenuOptions();
	};
}