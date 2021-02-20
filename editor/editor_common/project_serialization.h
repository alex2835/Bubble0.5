#pragma once

#include "engine.h"
#include <fstream>

namespace Bubble
{
    inline void ProjectSerialization(const std::string& path,
                                     const Loader&      loader,
                                     const Renderer&    renderer,
                                     const Scene&       scene)
    {
        nlohmann::json json;
        json["Scene"]    = SceneSerialization(scene, loader);
        json["Renderer"] = RendererSerialization(renderer, loader);
        json["Loader"]   = LoaderSerializetion(loader);

        std::ofstream fstream(path);
        fstream << json.dump(1);
        fstream.close();
    }

    inline void ProjectDeserialization(const std::string& path,
                                       Loader&   loader,
                                       Renderer& renderer,
                                       Scene&    scene)
    {
        std::ifstream ifstream(path);
        nlohmann::json json;

        if (!ifstream.is_open())
            throw std::runtime_error("Invalid path to project: " + path);

        ifstream >> json;
        ifstream.close();
        LoaderDeserializetion(json["Loader"], loader);
        RendererDeserialization(json["Renderer"], renderer, loader);
        SceneDeserialization(json["Scene"], scene, loader);
    }

}