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

        json["BackgroundType"] = (int)renderer.mSceneStage.mBackgroundType;

        json["ClearColor"] = to_json(renderer.mSceneStage.mClearColor);

        json["SkyboxBlendFactor"]   = renderer.mSceneStage.mSkyboxBlendFactor;
        json["SkyboxBrightness"]    = renderer.mSceneStage.mSkyboxBrightness;
        json["SkyboxRotation"]      = renderer.mSceneStage.mSkyboxRotation;
        json["SkyboxRotationSpeed"] = renderer.mSceneStage.mSkyboxRotationSpeed;

        auto skybox_first = std::find_if(loader.mLoadedSkyboxes.begin(), loader.mLoadedSkyboxes.end(),
            [&renderer](const auto& pair) { return pair.second == renderer.mSceneStage.mSkyboxFirst; });

        auto skybox_second= std::find_if(loader.mLoadedSkyboxes.begin(), loader.mLoadedSkyboxes.end(),
            [&renderer](const auto& pair) { return pair.second == renderer.mSceneStage.mSkyboxSecond; });
        
        auto skysphere_texture = std::find_if(loader.mLoadedSkyspheres.begin(), loader.mLoadedSkyspheres.end(),
            [&renderer](const auto& pair) { return pair.second == renderer.mSceneStage.mSkysphereTexture; });

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
        renderer.mSceneStage.mBackgroundType = json["BackgroundType"];

        renderer.mSceneStage.mClearColor = from_json_vec4(json["ClearColor"]);

        renderer.mSceneStage.mSkyboxBlendFactor   = json["SkyboxBlendFactor"];
        renderer.mSceneStage.mSkyboxBrightness    = json["SkyboxBrightness"];
        renderer.mSceneStage.mSkyboxRotation      = json["SkyboxRotation"];
        renderer.mSceneStage.mSkyboxRotationSpeed = json["SkyboxRotationSpeed"];

        if (json_exists(json, "SkyboxFirst"))
            renderer.mSceneStage.mSkyboxFirst = loader.LoadSkybox(json["SkyboxFirst"]);

        if (json_exists(json, "SkyboxSecond"))
            renderer.mSceneStage.mSkyboxSecond = loader.LoadSkybox(json["SkyboxSecond"]);

        if (json_exists(json, "Skysphere"))
            renderer.mSceneStage.mSkysphereTexture = loader.LoadSkysphere(json["Skysphere"]);
    }
}