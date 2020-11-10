#pragma once

#include "camera/free_camera.h"
#include "viewport/viewport.h"
#include "skybox/skybox_loader.h"
#include "shader/shader_loader.h"
#include "renderer/renderer.h"
#include "input/input.h"
#include "file_dialog.h"

#include "imgui.h"


namespace Bubble
{
	struct SkyboxExplorer
	{
		Ref<Skybox> mSelectedSkybox = nullptr;
		FreeCamera mCamera;
		Viewport mViewport;
		Ref<Shader> mShader;

		// Active components
		std::string mNames;
		int nSelectedFirts = 0;
		int nSelectedSecond= 0;

		SkyboxExplorer();

		void RenderSelectedSkybox();
		void Draw(bool* is_open, DeltaTime dt);
	};
}