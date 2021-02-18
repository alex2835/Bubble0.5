#pragma once

#include "texture.h"
#include "shader.h"
#include "model.h"
#include "skybox.h"
#include <unordered_map>
#include <exception>

namespace Bubble
{
    struct Loader
    {
        std::unordered_map<std::string, Ref<Texture2D>> mLoadedTextures;
        std::unordered_map<std::string, Ref<Model>>     mLoadedModels;
        std::unordered_map<std::string, Ref<Shader>>    mLoadedShaders;
        std::unordered_map<std::string, Ref<Skybox>>    mLoadedSkyboxes;

        // ================ Textures ================
    public:
        Ref<Texture2D> LoadTexture2DSingleColor(const std::string& name, const glm::vec4& color);
        Ref<Texture2D> LoadTexture2D(std::string path, const Texture2DSpecification& spec = {});

        std::tuple<Scope<uint8_t[]>, Texture2DSpecification>
            OpenRawImage(const std::string& path, Texture2DSpecification spec = {});

        // ================= Meshes ================= 
    public:
        Ref<Model> LoadModel(std::string path);

       // ================= Shaders ================= 
    public:
        Ref<Shader> LoadShader(const std::string& path);

        Ref<Shader> LoadShader(const std::string& name,
                               const std::string& vertex,
                               const std::string& fragment,
                               const std::string& geometry = std::string());

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
        Ref<Skybox> LoadSkybox(std::string file);
    };

}