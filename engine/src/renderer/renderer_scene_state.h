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
        float mSkyboxBlendFactor = 0.0f;
        float mSkyboxBrightness  = 0.0f;
        float mSkyboxRotation    = 0.0f;
        float mSkyboxRotationSpeed = 0.0f;

        // Skysphere
        Ref<Texture2D> mSkysphereTexture;

        // Clear color
        glm::vec4 mClearColor;

        // Lights
        std::vector<GLSL_Light> mActiveLights;
    };

}