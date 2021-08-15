#pragma once

#include "bubble.h"

namespace Bubble
{
    struct UIArgs
    {
        Engine*      mEngine;
        Project*     mProject;
        Renderer*    mRenderer;
        Loader*      mLoader;
        Input*       mInput;
        
        Scene*       mScene;
        SceneCamera* mSceneCamera;
        Viewport*    mMainViewport;

        // Rendering options
        //bool mWireframeOption   = false;
        //bool mBoundingBoxOption = false;
    };

}