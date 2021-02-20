#pragma once

#include "scene/scene.h"
#include "scene/components.h"
#include "nlohmann/json.hpp"
#include "entt/entt.hpp"

namespace Bubble
{
    // ================= Archives ===================
    struct OutputArchive
    {
        nlohmann::json mJson;
        Loader& mLoader;

        OutputArchive(Loader& loader)
            : mLoader(loader)
        {}

        void operator()(entt::entity entity)
        {
            mJson["Entities"].push_back((uint32_t)entity);
        }

        void operator()(std::underlying_type_t<entt::entity> size)
        {
            mJson["Size"].push_back(size);
        }

        template <typename T>
        void operator() (entt::entity entity, const T& component)
        {
            nlohmann::json entity_component;
            entity_component["Entity"] = entity;
            entity_component["Component"] = component.Serialize(mLoader);
            mJson["Components"].push_back(entity_component);
        };

    };

    struct InputArchive
    {
        const nlohmann::json& mJson;
        Loader& mLoader;
        int mEtityIndex = 0;
        int mSizeIndex = 0;
        int mComponetIndex = 0;

        InputArchive(const nlohmann::json& json, Loader& loader)
            : mJson(json),
            mLoader(loader)
        {}

        void operator()(entt::entity& entity)
        {
            entity = mJson["Entities"][mEtityIndex++];
        }

        void operator()(std::underlying_type_t<entt::entity>& size)
        {
            size = mJson["Size"][mSizeIndex++];
        }

        template <typename T>
        void operator() (entt::entity& entity, T& component)
        {
            nlohmann::json entity_component = mJson["Components"][mComponetIndex++];
            entity = entity_component["Entity"];
            component.Deserialize(entity_component["Component"], mLoader);
        };

    };


    // ==================== Serialization ======================
    inline nlohmann::json SerializeScene(const entt::registry& scene, Loader& loader)
    {
        OutputArchive output(loader);
        entt::snapshot{ scene }
            .entities(output)
            .component<TagComponent, PositionComponent, RotationComponent, ScaleComponent, TransformComponent, LightComponent, ModelComponent>(output);
        return output.mJson;
    }

    inline void DeserializeScene(const nlohmann::json& json, entt::registry& scene, Loader& loader)
    {
        InputArchive input(json, loader);
        scene.clear();

        entt::snapshot_loader{ scene }
            .entities(input)
            .component<TagComponent, PositionComponent, RotationComponent, ScaleComponent, TransformComponent, LightComponent, ModelComponent>(input)
            .orphans();
    }
}