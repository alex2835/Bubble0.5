#pragma once

#include "engine.h"
#include "imgui.h"
#include "file_dialog.h"
#include "viewport/viewport.h"


namespace Bubble
{
	struct SkyboxExplorer
	{
		Ref<Skybox> mSelectedSkybox = nullptr;
		FreeCamera mCamera;
		Viewport mViewport;
		Ref<Shader> mShader;

		SkyboxExplorer();

		void RenderSelectedSkybox();
		void Draw(bool* is_open, DeltaTime dt);
	};
}