
#include "model_loader.h"


namespace Bubble
{
	std::vector<std::pair<std::string, Ref<Model>>>  ModelLoader::s_LoadedModels;
	

	Ref<Model> ModelLoader::StaticModel(const std::string& path)
	{
		for (const auto& stored_model : s_LoadedModels) {
			if (stored_model.first == path) {
				return stored_model.second;
			}
		}
		auto model = CreateRef<Model>();
		s_LoadedModels.push_back(std::make_pair(path, model));

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenNormals);
		if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode)
		{
			throw std::runtime_error("ERROR::ASSIMP\n" + std::string(importer.GetErrorString()));
		}

		// process ASSIMP's root node recursively
		//model.Meshes.reserve(scene->mNumMeshes);
		ProcessNode(*model, scene->mRootNode, scene);

		return model;
	}

	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void ModelLoader::ProcessNode(Model& model, aiNode* node, const aiScene* scene)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			model.Meshes.emplace_back(ProcessMesh(mesh, scene));
		}
	
		for (int i = 0; i < node->mNumChildren; i++) {
			ProcessNode(model, node->mChildren[i], scene);
		}
	}
	
	Mesh ModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		// data to fill
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<MeshTexture> textures;
	
		vertices.reserve(mesh->mNumVertices);
		indices.reserve(mesh->mNumFaces);
		textures.reserve(5);
	
		// Walk through each of the mesh's vertices
		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
	
			// positions
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;
	
			// normals
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
	
			// texture coordinates
			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vec;
				// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else {
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			}
	
			// tangent
			if (mesh->mTangents)
			{
				vector.x = mesh->mTangents[i].x;
				vector.y = mesh->mTangents[i].y;
				vector.z = mesh->mTangents[i].z;
				vertex.Tangent = vector;
				// bitangent
				vector.x = mesh->mBitangents[i].x;
				vector.y = mesh->mBitangents[i].y;
				vector.z = mesh->mBitangents[i].z;
				vertex.Bitangent = vector;
			}
	
			vertices.push_back(vertex);
		}
	
		// now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			// retrieve all indices of the face and store them in the indices vector
			for (int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}
	
		// process materials
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	
		// 1. diffuse maps
		LoadMaterialTextures(textures, material, aiTextureType_DIFFUSE, TextureType::DIFFUSE);
		// 2. specular maps
		LoadMaterialTextures(textures, material, aiTextureType_SPECULAR, TextureType::SPECULAR);
		// 3. normal maps
		LoadMaterialTextures(textures, material, aiTextureType_HEIGHT, TextureType::NORMAL);
		// 4. height maps
		LoadMaterialTextures(textures, material, aiTextureType_AMBIENT, TextureType::HEIGHT);
	
		auto vertices_ref = CreateRef<std::vector<Vertex>>(std::move(vertices));
		auto indices_ref = CreateRef<std::vector<uint32_t>>(std::move(indices));
		auto textures_ref = CreateRef<std::vector<MeshTexture>>(std::move(textures));
		return Mesh(vertices_ref, indices_ref, textures_ref);
	}
	
	// checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	void ModelLoader::LoadMaterialTextures(std::vector<MeshTexture>& textures, aiMaterial* mat, aiTextureType type, TextureType texture_type)
	{
		// retrieve the directory path of the filepath
		const std::string& path = s_LoadedModels.back().first;
		std::string directory = path.substr(0, path.find_last_of('/') + 1);
	
		for (int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			
			MeshTexture texture(directory + str.C_Str());
			texture.type = texture_type;
			textures.push_back(std::move(texture));
		}
	}

}