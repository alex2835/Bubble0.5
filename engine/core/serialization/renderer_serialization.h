#pragma once

#include "nlohmann/json.hpp"
#include "renderer.h"

namespace Bubble
{
    static inline nlohmann::json to_json(const glm::vec4& vec);
    static inline glm::vec4 from_json_vec4(const nlohmann::json& j);
    static inline bool json_exists(const nlohmann::json& j, const std::string& key);

    inline nlohmann::json RendererSerialization(const Renderer& renderer, const Loader& loader)
    {
        nlohmann::json json;

        json["BackgroundType"] = (int)renderer.mSceneState.mBackgroundType;

        json["ClearColor"] = to_json(renderer.mSceneState.mClearColor);

        json["SkyboxBlendFactor"]   = renderer.mSceneState.mSkyboxBlendFactor;
        json["SkyboxBrightness"]    = renderer.mSceneState.mSkyboxBrightness;
        json["SkyboxRotation"]      = renderer.mSceneState.mSkyboxRotation;
        json["SkyboxRotationSpeed"] = renderer.mSceneState.mSkyboxRotationSpeed;

        auto skybox_first = std::find_if(loader.mLoadedSkyboxes.begin(), loader.mLoadedSkyboxes.end(),
            [&renderer](const auto& pair) { return pair.second == renderer.mSceneState.mSkyboxFirst; });

        auto skybox_second= std::find_if(loader.mLoadedSkyboxes.begin(), loader.mLoadedSkyboxes.end(),
            [&renderer](const auto& pair) { return pair.second == renderer.mSceneState.mSkyboxSecond; });
        
        auto skysphere_texture = std::find_if(loader.mLoadedSkyspheres.begin(), loader.mLoadedSkyspheres.end(),
            [&renderer](const auto& pair) { return pair.second == renderer.mSceneState.mSkysphereTexture; });

        if (skybox_first != loader.mLoadedSkyboxes.end())
            json["SkyboxFirst"] = skybox_first->first;

        if (skybox_second != loader.mLoadedSkyboxes.end())
            json["SkyboxSecond"] = skybox_second->first;

        if (skysphere_texture != loader.mLoadedSkyspheres.end())
            json["Skysphere"] = skysphere_texture->first;

        return json;
    }

    inline void RendererDeserialization(const nlohmann::json& json, Renderer& renderer, Loader& loader)
    {
        renderer.mSceneState.mBackgroundType = json["BackgroundType"];

        renderer.mSceneState.mClearColor = from_json_vec4(json["ClearColor"]);

        renderer.mSceneState.mSkyboxBlendFactor   = json["SkyboxBlendFactor"];
        renderer.mSceneState.mSkyboxBrightness    = json["SkyboxBrightness"];
        renderer.mSceneState.mSkyboxRotation      = json["SkyboxRotation"];
        renderer.mSceneState.mSkyboxRotationSpeed = json["SkyboxRotationSpeed"];

        if (json_exists(json, "SkyboxFirst"))
            renderer.mSceneState.mSkyboxFirst = loader.LoadAndCacheSkybox(loader.mProject.GetPath() + std::string(json["SkyboxFirst"]));

        if (json_exists(json, "SkyboxSecond"))
            renderer.mSceneState.mSkyboxSecond = loader.LoadAndCacheSkybox(loader.mProject.GetPath() + std::string(json["SkyboxSecond"]));

        if (json_exists(json, "Skysphere"))
            renderer.mSceneState.mSkysphereTexture = loader.LoadAndCacheTexture2D(loader.mProject.GetPath() + std::string(json["Skysphere"]));
    }
}