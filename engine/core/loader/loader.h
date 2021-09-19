#pragma once

#include "texture.h"
#include "shader.h"
#include "model.h"
#include "skybox.h"
#include "project.h"

#include <unordered_map>
#include <exception>

namespace Bubble
{
    struct Loader
    {
        Project& mProject;

        // Storage
        std::unordered_map<std::string, Ref<Texture2D>> mLoadedTextures;
        std::unordered_map<std::string, Ref<Model>>     mLoadedModels;
        std::unordered_map<std::string, Ref<Shader>>    mLoadedShaders;
        std::unordered_map<std::string, Ref<Skybox>>    mLoadedSkyboxes;
        std::unordered_map<std::string, Ref<Texture2D>> mLoadedSkyspheres;

        std::unordered_map<std::string, Ref<Texture2D>> mSystemTextures;
        std::unordered_map<std::string, Ref<Model>>     mSystemModels;
        std::unordered_map<std::string, Ref<Shader>>    mSystemShaders;

        Loader(Project& prj);
        void LoadSystemResources();
        std::string CopyToProject(std::string file_path, std::string type);

		void LoadSystemModel(std::string path);
		Ref<Model> GetSystemModel(std::string name);

		void LoadSystemTexture(std::string path, Texture2DSpecification spec = {});
		Ref<Texture2D> GetSystemTexture(std::string name);

		void LoadSystemShader(const std::string& name,
			const std::string& vertex,
			const std::string& fragment,
			const std::string& geometry = std::string());

		Ref<Shader> GetSystemShader(const std::string& name);


        // ================ Textures ================
        Ref<Texture2D> LoadAndCacheTexture2D(std::string path, const Texture2DSpecification& spec = {});

        Ref<Texture2D> LoadTexture2DSingleColor(const std::string& name, const glm::vec4& color);
        Ref<Texture2D> LoadTexture2D(std::string path, const Texture2DSpecification& spec = {});
        std::tuple<Scope<uint8_t[]>, Texture2DSpecification>
            OpenRawImage(const std::string& path, Texture2DSpecification spec = {});

        // ================= Meshes ================= 
        Ref<Model> LoadAndCacheModel(std::string path);
        Ref<Model> LoadModel(std::string path, std::string path_in_project = {});

        // ================= Shaders ================= 
        Ref<Shader> LoadAndCacheShader(const std::string& path);
        Ref<Shader> LoadShader(const std::string& path);


    private:
        void ParseShaders(const std::string& path,
                          std::string& vertex,
                          std::string& fragment,
                          std::string& geometry);

        void CompileShaders(Shader& shader,
                            const std::string& vertex_source,
                            const std::string& fragment_source,
                            const std::string& geometry_source);

        // ================= Skyboxes ================= 
    public:
        // Directory with (top.png, bot.png, ...)
        Ref<Skybox> LoadSkyboxFromDir(const std::string& dir, const std::string& ext = ".jpg");

        // Single file skybox
        Ref<Skybox> LoadAndCacheSkybox(std::string file);
        Ref<Skybox> LoadSkybox(std::string file);

        // ================= Skysphere ================= 
        Ref<Texture2D> LoadSkysphere(const std::string& path);
    };

}