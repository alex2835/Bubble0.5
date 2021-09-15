#pragma once

#include "bubble.h"
#include "ui_loader.h"
#include "scene_camera.h"
#include "viewport.h"
//#include "project_serialization.h"

namespace Bubble
{
	class EditorLayer : public Layer
	{
		Engine&		mEngine;
		UILoader	mUILoader;
		SceneCamera mSceneCamera;
		Viewport    mViewport;

	public:
		EditorLayer(Engine& Engine);
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(DeltaTime dt) override;
		void OnEvent(SDL_Event& event) override;

	private:
		UIArgs GetUIArgs();
	};
}