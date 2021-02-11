#pragma once

#include "renderer_base.h"
#include "model.h"
#include "skybox.h"
#include "shader.h"

#include <unordered_map>
#include <exception>


namespace Bubble
{
    class Loader
    {
    public:
        std::unordered_map<std::string, Ref<Model>>  mLoadedModels;
        std::unordered_map<std::string, Ref<Shader>> mLoadedShaders;
        std::unordered_map<std::string, Ref<Skybox>> mLoadedSkyboxes;

        // ================= Meshes ================= 
    public:
        Ref<Model> StaticModel(std::string path);

    //private:
    //    void ProcessNode(Model& model, aiNode* node, const aiScene* scene, const std::string& path);
    //    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, const std::string& path);
    //    DefaultMaterial LoadMaterialTextures(aiMaterial* mat, const std::string& path);

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