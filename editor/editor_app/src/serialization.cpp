
#include "serialization.h"


namespace Bubble
{
	void SaveProject(const std::string& path, Scene* scene)
	{
		//nlohmann::json json;
		//
		//// Save scene
		//json["Scene"] = SerializeScene(scene->Registry);
		//
		//// Save skyboxes
		//for (const auto& [path, skybox] : *Loader::sLoadedSkyboxes)
		//{
		//	json["Skybox"]["Paths"].push_back(path);
		//}
		//json["Skybox"]["First"]  = ui->mScenePanel->SelectedSkyboxNameFirst;
		//json["Skybox"]["Second"] = ui->mScenePanel->SelectedSkyboxNameSecond;
		//json["Skybox"]["Brightness"] = Renderer::sSkyboxBrightness;
		//json["Skybox"]["BlendFactor"] = Renderer::sSkyboxBlendFactor;
		//json["Skybox"]["Rotation"] = Renderer::sSkyboxRotation;
		//
		//// Save models
		//for (const auto& [path, model] : *Loader::sLoadedModels)
		//{
		//	json["Model"]["Paths"].push_back(path);
		//}
		//
		//json["Skybox"]["FirstID"]  = ui->mScenePanel->SelectedSkyboxFirstID;
		//json["Skybox"]["SecondID"] = ui->mScenePanel->SelectedSkyboxSecondID;
		//
		//// Dump
		//std::ofstream fstream(path);
		//fstream << json.dump(1);
		//fstream.close();
	}

	void OpenProject(const std::string& path, Scene* scene)
	{
        //std::ifstream ifstream(path);
        //nlohmann::json json;
        //
        //if (!ifstream.is_open())
        //	throw std::runtime_error("Path to project not valid : " + path);
        //
        //ifstream >> json;
        //ifstream.close();
        //
        //// Load skyboxes
        //for (const auto& path : json["Skybox"]["Paths"])
        //{
        //	Loader::LoadSkybox(path);
        //}
        //Renderer::sSkyboxFirst  = Loader::LoadSkybox(json["Skybox"]["First"]);
        //Renderer::sSkyboxSecond = Loader::LoadSkybox(json["Skybox"]["Second"]);
        //Renderer::sSkyboxBrightness = json["Skybox"]["Brightness"];
        //Renderer::sSkyboxBlendFactor = json["Skybox"]["BlendFactor"];
        //Renderer::sSkyboxRotation = json["Skybox"]["Rotation"];
        //
        //// Load models
        //for (const auto& path : json["Model"]["Paths"])
        //{
        //	Loader::StaticModel(path);
        //}
        //
        //// Load scene
        //DeserializeScene(scene->Registry, json["Scene"]);
        //
        //// Load UI state
        //ui->mScenePanel->SelectedSkyboxFirstID  = json["Skybox"]["FirstID"];
        //ui->mScenePanel->SelectedSkyboxSecondID = json["Skybox"]["SecondID"];
	}

}

