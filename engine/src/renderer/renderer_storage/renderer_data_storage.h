#pragma once

#include "buffer.h"
#include "vertex_array.h"
#include "shader.h"
#include "loader.h"

namespace Bubble
{
    struct RendererStorage
    {
        Ref<VertexArray> mSkyboxVertexArray;
        Ref<Shader>      mPhongShader;
        Ref<Shader>      mSkyboxShader;

        RendererStorage();
    };
}