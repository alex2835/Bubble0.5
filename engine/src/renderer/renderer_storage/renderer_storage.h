#pragma once

#include "buffer.h"
#include "vertex_array.h"
#include "shader.h"
#include "loader.h"

namespace Bubble
{
    struct RendererStorage
    {
        // Skies
        Ref<Model> mSphere;
        Ref<VertexArray> mSkyboxVertexArray;

        // Internal Shaders
        Ref<Shader> mPhongShader;
        Ref<Shader> mSkyboxShader;
        // Frustum culling planes;
        glm::vec4   mFrustumPlanes[6];

        RendererStorage(Loader* loader);
    };
}