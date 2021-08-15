#pragma once

#include <string>

namespace Bubble
{
    class Engine;

    void ProjectSerialization(const Engine& engine);
    void ProjectDeserialization(const std::string& path, Engine& engine);
}