#pragma once 

#include "model.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <exception>


namespace Bubble
{
	class ModelLoader
	{
		static std::vector<std::pair<std::string, Ref<Model>>> s_LoadedModels;
		 
	public:
		static Ref<Model> StaticModel(const std::string& path);
		
	private:
		static void ProcessNode(Model& model, aiNode* node, const aiScene* scene);
		static Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		static void LoadMaterialTextures(std::vector<MeshTexture>& textures, aiMaterial* mat, aiTextureType type, TextureType texture_type);
	};
	
}