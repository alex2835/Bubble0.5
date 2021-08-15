
#include "engine/engine.h"
#include "serialization.h"
#include "renderer_serialization.h"
#include "loader_serialization.h"
#include "entity_serialization.h"
#include "nlohmann/json.hpp"
#include <fstream>

namespace Bubble
{
    void ProjectSerialization(const Engine& engine)
    {
        nlohmann::json json;
        json["Scene"]    = SceneSerialization(engine.GetScene(), engine.GetLoader());
        json["Renderer"] = RendererSerialization(engine.GetRenderer(), engine.GetLoader());
        json["Loader"]   = LoaderSerializetion(engine.GetLoader());

        std::ofstream fstream(engine.GetProject().GetPathWithName());
        fstream << json.dump(1);
        fstream.close();
    }

    void ProjectDeserialization(const std::string& path, Engine& engine)
    {
        std::ifstream ifstream(path);
        nlohmann::json json;

        if (!ifstream.is_open())
            throw std::runtime_error("Invalid path to project: " + path);

        ifstream >> json;
        ifstream.close();

        engine.GetProject().Open(path);
        LoaderDeserializetion(json["Loader"], engine.GetLoader());
        RendererDeserialization(json["Renderer"], engine.GetRenderer(), engine.GetLoader());
        SceneDeserialization(json["Scene"], engine.GetScene(), engine.GetLoader());
    }

}