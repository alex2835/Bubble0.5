#pragma once

#include "renderer_base.h"
#include "vertex_array.h"
#include "framebuffer.h"
#include "shader.h"
#include "model.h"
#include "skybox.h"
#include "buffer.h"
#include "camera.h"
#include "light.h"
#include "uniform_buffer.h"

namespace Bubble
{
    struct RendererSceneStage
    {
        // Skyboxes
        Ref<Skybox> mSkyboxFirst;
        Ref<Skybox> mSkyboxSecond;
        float mSkyboxBlendFactor;
        float mSkyboxBrightness;
        float mSkyboxRotation;
        float mSkyboxRotationSpeed;

        // Lights
        std::vector<GLSL_Light> mActiveLights;
    };

}