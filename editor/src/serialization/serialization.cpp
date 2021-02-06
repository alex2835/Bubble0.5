
#include "serialization.h"


namespace Bubble
{
	void SaveProject(const std::string& path, Scene* scene, UI* ui)
	{
		nlohmann::json json;

		// Save scene
		json["Scene"] = SerializeScene(scene->Registry);

		// Save skyboxes
		for (const auto& [path, skybox] : SkyboxLoader::sLoadedSkyboxes)
		{
			json["Skybox"]["Paths"].push_back(path);
		}
		json["Skybox"]["First"] = SkyboxLoader::sLoadedSkyboxes[ui->mScenePanel.nSelectedFirts].first;
		json["Skybox"]["Second"] = SkyboxLoader::sLoadedSkyboxes[ui->mScenePanel.nSelectedSecond].first;
		json["Skybox"]["Brightness"] = Renderer::sSkyboxBrightness;
		json["Skybox"]["BlendFactor"] = Renderer::sSkyboxBlendFactor;
		json["Skybox"]["Rotation"] = Renderer::sSkyboxRotation;

		// Save models
		for (const auto& [path, model] : ModelLoader::LoadedModels)
		{
			json["Model"]["Paths"].push_back(path);
		}

		// Save UI state
		json["Skybox"]["FirstID"] = ui->mScenePanel.nSelectedFirts;
		json["Skybox"]["SecondID"] = ui->mScenePanel.nSelectedSecond;

		// Dump
		std::ofstream fstream(path);
		fstream << json.dump(1);
		fstream.close();
	}

	void OpenProject(const std::string& path, Scene* scene, UI* ui)
	{
		std::ifstream ifstream(path);
		nlohmann::json json;

		if (!ifstream.is_open())
			throw std::runtime_error("Path to project not valid : " + path);
		
		ifstream >> json;
		ifstream.close();

		// Load skyboxes
		for (const auto& path : json["Skybox"]["Paths"])
		{
			SkyboxLoader::Load(path);
		}
		Renderer::sSkyboxFirst = SkyboxLoader::Load(json["Skybox"]["First"]);
		Renderer::sSkyboxSecond = SkyboxLoader::Load(json["Skybox"]["Second"]);
		Renderer::sSkyboxBrightness = json["Skybox"]["Brightness"];
		Renderer::sSkyboxBlendFactor = json["Skybox"]["BlendFactor"];
		Renderer::sSkyboxRotation = json["Skybox"]["Rotation"];

		// Load models
		for (const auto& path : json["Model"]["Paths"])
		{
			ModelLoader::StaticModel(path);
		}

		// Load scene
		DeserializeScene(scene->Registry, json["Scene"]);

		// Load UI state
		ui->mScenePanel.nSelectedFirts = json["Skybox"]["FirstID"];
		ui->mScenePanel.nSelectedSecond = json["Skybox"]["SecondID"];
	}

}

