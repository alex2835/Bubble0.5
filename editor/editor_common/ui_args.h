#pragma once

#include "engine.h"
#include "viewport.h"
#include "scene_camera.h"

namespace Bubble
{
    struct UIArgs
    {
        Renderer*    mRenderer;
        Loader*      mLoader;
        Input*       mInput;
        
        Scene*       mScene;
        SceneCamera* mSceneCamera;
        Viewport*    mMainViewport;

        // Rendering options
        bool mWireframeOption   = false;
        bool mBoundingBoxOption = false;
    };

}