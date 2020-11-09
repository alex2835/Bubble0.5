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
		Ref<Model> mSelectedModel = nullptr;

		ThirdPersonCamera mCamera;
		Viewport mViewport;
		Ref<Shader> mShader;
		Light mLight;
	
	public:
		ModelExplorer();
		void Draw(bool* is_open, DeltaTime dt);

	private:
		void RenderSelectedModel();
	};

}