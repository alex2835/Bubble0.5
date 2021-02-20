#pragma once

#include "nlohmann/json.hpp"
#include "renderer.h"

namespace Bubble
{
    inline nlohmann::json RendererSerialization(const Renderer& renderer)
    {
        nlohmann::json json;
        

        return json;
    }

    inline void RendererDeserialization(const nlohmann::json& json, Renderer& renderer)
    {

    }
}