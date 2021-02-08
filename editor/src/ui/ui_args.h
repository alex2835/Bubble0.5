#pragma once

#include "viewport/viewport.h"
#include "scene_camera/scene_camera.h"


namespace Bubble
{
    struct UIArgs
    {
        SceneCamera* mSceneCamera;
        Viewport* mMainViewport;
        Scene* mScene;
    };

}