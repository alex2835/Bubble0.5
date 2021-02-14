
#include "ui_loader.h"

namespace Bubble
{
	UILoader::UILoader(Window* window)
        : mImGuiControl(window),
		  mUIDLL("../editor_ui/BubbleEditorUI")
    {
        mImGuiControl.OnAttach();
		mUIDLL.Call<void(ImGuiContext*)>("OnInit", mImGuiControl.mContext);
    }

	UILoader::~UILoader()
	{
		mImGuiControl.OnDetach();
	}

	void UILoader::OnUpdate(DeltaTime dt)
	{
		mImGuiControl.Begin();
			mImGuiControl.BeginMenuBar();
				mUIDLL.Call<void()>("OnMenuDraw");
			mImGuiControl.EndMenuBar();

			mUIDLL.Call<void(DeltaTime, UIArgs)>("OnDraw", dt, mArgs);
		mImGuiControl.End();
		
        mUIDLL.Call<void(DeltaTime)>("OnUpdate", dt);

		if (mUIDLL.CheckForUpdate())
		{
            mUIDLL.Call<void(ImGuiContext*)>("OnInit", mImGuiControl.mContext);
		}
	}

    void UILoader::OnEvent(SDL_Event& event)
    {
        mImGuiControl.OnEvent(event);
    }

}
