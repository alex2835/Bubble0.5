#pragma once

#include "loader.h"
#include "nlohmann/json.hpp"

namespace Bubble
{
    static inline bool json_exists(const nlohmann::json& j, const std::string& key);

    inline nlohmann::json LoaderSerializetion(const Loader& loader)
    {
        nlohmann::json json;
        for (const auto& [path, someting] : loader.mLoadedTextures)
        {
            json["Textures"].push_back(path);
        }
        for (const auto& [path, someting] : loader.mLoadedShaders)
        {
            json["Shaders"].push_back(path);
        }
        for (const auto& [path, someting] : loader.mLoadedSkyboxes)
        {
            json["Skyboxes"].push_back(path);
        }
        for (const auto& [path, someting] : loader.mLoadedSkypsheres)
        {
            json["Skyspheres"].push_back(path);
        }
        for (const auto& [path, someting] : loader.mLoadedModels)
        {
            json["Models"].push_back(path);
        }
        return json;
    }

    inline void LoaderDeserializetion(const nlohmann::json& json, Loader& loader)
    {
        if (json_exists(json, "Textures"))
        {
            for (const auto& path : json["Textures"])
            {
                loader.LoadTexture2D(path);
            }
        }
        if (json_exists(json, "Shaders"))
        {
            for (const auto& path : json["Shaders"])
            {
                loader.LoadShader(path);
            }
        }
        if (json_exists(json, "Skyboxes"))
        {
            for (const auto& path : json["Skyboxes"])
            {
                loader.LoadSkybox(path);
            }
        }
        if (json_exists(json, "Skyspheres"))
        {
            for (const auto& path : json["Skyspheres"])
            {
                loader.LoadSkysphere(path);
            }
        }
        if (json_exists(json, "Models"))
        {
            for (const auto& path : json["Models"])
            {
                loader.LoadModel(path);
            }
        }
    }
}