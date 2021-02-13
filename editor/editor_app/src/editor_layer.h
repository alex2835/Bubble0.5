#pragma once

#include "engine.h"
#include "ui_loader.h"
#include "scene_camera.h"

namespace Bubble
{
	class EditorLayer : public Layer
	{
		Window*  mWindow;
        UILoader mUILoader;

		Renderer    mRenderer;
		Loader      mLoader;
		Scene       mScene;
        SceneCamera mSceneCamera;
        Viewport    mViewport;

		// Options
		bool mClearScreanOption = false;

	public:
		EditorLayer(Window* window);
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(DeltaTime dt) override;
		void OnEvent(SDL_Event& event) override;
	};
}