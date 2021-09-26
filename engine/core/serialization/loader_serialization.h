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
            json["Textures"].push_back(path);
        
        for (const auto& [path, someting] : loader.mLoadedShaders)
            json["Shaders"].push_back(path);
        
        for (const auto& [path, someting] : loader.mLoadedSkyboxes)
            json["Skyboxes"].push_back(path);
        
        for (const auto& [path, someting] : loader.mLoadedSkyspheres)
            json["Skyspheres"].push_back(path);
        
        for (const auto& [path, someting] : loader.mLoadedModels)
            json["Models"].push_back(path);
        return json;
    }

    inline void LoaderDeserializetion(const nlohmann::json& json, Loader& loader)
    {
        if (json_exists(json, "Textures"))
            for (const std::string& rel_path : json["Textures"])
                loader.LoadAndCacheTexture2D(loader.mProject.GetPath() + rel_path);
        
        if (json_exists(json, "Shaders"))
            for (const std::string& rel_path : json["Shaders"])
                loader.LoadShader(loader.mProject.GetPath() + rel_path);
        
        if (json_exists(json, "Skyboxes"))
            for (const std::string& rel_path : json["Skyboxes"])
                loader.LoadSkybox(loader.mProject.GetPath() + rel_path);
        
        if (json_exists(json, "Skyspheres"))
            for (const std::string& rel_path : json["Skyspheres"])
                loader.LoadSkysphere(loader.mProject.GetPath() + rel_path);
        
        if (json_exists(json, "Models"))
            for (const std::string& rel_path : json["Models"])
                loader.LoadModel(loader.mProject.GetPath() + rel_path);
    }
}