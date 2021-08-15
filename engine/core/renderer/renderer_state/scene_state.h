#pragma once

#include "core/renderer_base.h"
#include "core/vertex_array.h"
#include "core/framebuffer.h"
#include "core/shader.h"
#include "core/model.h"
#include "core/skybox.h"
#include "core/buffer.h"
#include "core/camera.h"
#include "core/light.h"
#include "core/uniform_buffer.h"

namespace Bubble
{
    enum class BackgroundType { COLOR, SKYBOX, SKYSPHERE };

    struct RendererSceneState
    {
        BackgroundType mBackgroundType = BackgroundType::COLOR;

        // Clear color
        glm::vec4 mClearColor;

        // Skyboxes
        Ref<Skybox> mSkyboxFirst;
        Ref<Skybox> mSkyboxSecond;
        float mSkyboxBlendFactor = 0.0f;
        float mSkyboxBrightness  = 0.0f;
        float mSkyboxRotation    = 0.0f;
        float mSkyboxRotationSpeed = 0.0f;

        // Skysphere
        Ref<Texture2D> mSkysphereTexture;

        // Lights
        std::vector<GLSL_Light> mActiveLights;
    };

}