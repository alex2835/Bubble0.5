#pragma once

#include "renderer/renderer_base.h"
#include "renderer/model.h"
#include "renderer/skybox.h"
#include "renderer/shader.h"

#include "assimp/Importer.hpp"
#include "assimp/Exporter.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <exception>


namespace Bubble
{
    class Loader
    {
    public:
        static std::vector<std::pair<std::string, Ref<Model>>>  sLoadedModels;
        static std::vector<std::pair<std::string, Ref<Shader>>> sLoadedShaders;
        static std::vector<std::pair<std::string, Ref<Skybox>>> sLoadedSkyboxes;


        // ================= Meshes ================= 
    public:
        static Ref<Model> StaticModel(std::string path);

    private:
        static void ProcessNode(Model& model, aiNode* node, const aiScene* scene);
        static Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
        static DefaultMaterial LoadMaterialTextures(aiMaterial* mat);

        // ================= Shaders ================= 
    public:
        static Ref<Shader> LoadShader(const std::string& path);

        static Ref<Shader> LoadShader(const std::string& name,
                                      const std::string& vertex,
                                      const std::string& fragment,
                                      const std::string& geometry = std::string());

    private:
        static void ParseShaders(const std::string& path,
                                 std::string& vertex,
                                 std::string& fragment,
                                 std::string& geometry);

        static void CompileShaders(Shader& shader,
                                   const std::string& vertex_source,
                                   const std::string& fragment_source,
                                   const std::string& geometry_source);

        // ================= Skyboxes ================= 
    public:
        // Directory with (top.png, bot.png, ...)
        static Ref<Skybox> LoadSkyboxFromDir(const std::string& dir, const std::string& ext = ".jpg");

        // Single file skybox
        static Ref<Skybox> LoadSkybox(std::string file);
    };
}