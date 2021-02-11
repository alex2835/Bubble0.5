#pragma once

#include "imgui.h"
#include "engine.h"
#include "ui_args.h"
#include <atomic>

namespace Bubble
{

	struct UIModule
	{
	private:
		static std::atomic<int> sGlobalIDCounter;

	public:
		std::string mName;
		int  mWindowFlags;
		bool mIsOpen;
		int  mID;

		UIModule(const std::string& name);
		bool IsOpen();
		int GetID();

		// Called in imgui scope
		virtual void Draw(UIArgs args, DeltaTime dt) = 0;
		// Called out of imgui scope
		virtual void OnUpdate(UIArgs args, DeltaTime dt) {};
		virtual ~UIModule();
	};
}