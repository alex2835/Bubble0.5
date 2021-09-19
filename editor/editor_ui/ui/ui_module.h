#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"
#include "imgui.h"
#include "ui_args.h"

namespace Bubble
{
	struct UIModule
	{
		std::string mName;
		int  mWindowFlags;
		bool mIsOpen;

		UIModule(const std::string& name);
		bool IsOpen();

		// Called in imgui scope
		virtual void Draw(UIArgs args, DeltaTime dt) = 0;
		// Called out of imgui scope
		virtual void OnUpdate(UIArgs args, DeltaTime dt) {};
		virtual ~UIModule();
	};
}