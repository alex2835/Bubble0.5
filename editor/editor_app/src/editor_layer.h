#pragma once

#include "engine.h"
#include "ui_loader.h"
#include "scene_camera.h"
#include "project_serialization.h"

namespace Bubble
{
	class EditorLayer : public Layer
	{
		Window&		mWindow;
        Input&		mInput;
        UILoader	mUILoader;
        Loader      mLoader;
		Renderer    mRenderer;

		Scene       mScene;
        SceneCamera mSceneCamera;
        Viewport    mViewport;

	public:
		EditorLayer(Window& window, Input& input);
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(DeltaTime dt) override;
		void OnEvent(SDL_Event& event) override;
	};
}