#pragma once

#include "bubble.h"
#include "imgui.h"
#include "viewport.h"
#include "scene_camera.h"

namespace Bubble
{
    struct UIArgs
    {
        Engine*   mEngine   = nullptr;
        Project*  mProject  = nullptr;
        Renderer* mRenderer = nullptr;
        Loader*   mLoader   = nullptr;
        Input*    mInput    = nullptr;
        
        Scene*       mScene;
        SceneCamera* mSceneCamera;
        Viewport*    mMainViewport;

        // Rendering options
        //bool mWireframeOption   = false;
        //bool mBoundingBoxOption = false;
    };

}