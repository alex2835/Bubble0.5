#pragma once 

#include "nlohmann/json.hpp"
#include "fstream"
#include "ui.h"

namespace Bubble
{
    inline void UISerialization()
    {
        nlohmann::json json;
        for (const auto& ui_module : *UI::sModules)
            json["UI"][ui_module->mName] = ui_module->mIsOpen;
        
        std::ofstream fstream("./ui_state.json");
        fstream << json.dump(1);
        fstream.close();
    }

    inline void UIDeserialization()
    {
        std::ifstream  ifstream("./ui_state.json");
        nlohmann::json json;

        if (!ifstream.is_open())
            return;

        ifstream >> json;
        ifstream.close();
        for (const auto& ui_module : *UI::sModules)
            ui_module->mIsOpen = json["UI"][ui_module->mName];
    }
}