#pragma once

#define DHR_RELOAD_DELEY 600ms
#include "DHR.h"
#include "ui_args.h"
#include "imgui_control.h"

namespace Bubble
{
	struct UILoader
	{
        UIArgs mArgs;
        DLLHotReloader mUIDLL;
		ImGuiControl mImGuiControl;
		
        UILoader(Window& window);
        ~UILoader();
		void OnUpdate(DeltaTime dt);
		void OnEvent(SDL_Event& event);
	};

}