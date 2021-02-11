#pragma once

#include "viewport.h"
#include "scene_camera.h"

namespace Bubble
{
    struct UIArgs
    {
        SceneCamera* mSceneCamera;
        Viewport* mMainViewport;
        Scene* mScene;

        // Rendering options
        bool mWireframeOption = false;
        bool mBoundingBoxOption = false;
    };

}