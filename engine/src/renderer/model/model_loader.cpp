
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
	
		vertices.reserve(mesh->mNumVertices);
		indices.reserve(mesh->mNumFaces);
	
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
	
			if (mesh->mTangents)
			{
				// tangent
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
		aiMaterial* assimp_material = scene->mMaterials[mesh->mMaterialIndex];
		DefaultMaterial material = LoadMaterialTextures(assimp_material);

		auto vertices_ref = CreateRef<std::vector<Vertex>>(std::move(vertices));
		auto indices_ref = CreateRef<std::vector<uint32_t>>(std::move(indices));
		
		return Mesh(std::move(material), vertices_ref, indices_ref);
	}
	
	// checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	DefaultMaterial ModelLoader::LoadMaterialTextures(aiMaterial* mat)
	{
		const aiTextureType types[] = { aiTextureType_DIFFUSE , aiTextureType_SPECULAR, aiTextureType_HEIGHT, aiTextureType_NORMALS };
		
		DefaultMaterial material;
		for (int i = 0; i < 3; i++)
		{
			// retrieve the directory path of the filepath
			const std::string& path = s_LoadedModels.back().first;
			std::string directory = path.substr(0, path.find_last_of('/') + 1);
			
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < mat->GetTextureCount(types[i]); j++)
				{
					aiString str;
					mat->GetTexture(types[i], j, &str);

					switch (types[i])
					{
						case aiTextureType_DIFFUSE:
							material.DiffuseMaps.push_back(directory + str.C_Str());
							break;
						case aiTextureType_SPECULAR:
							material.SpecularMaps.push_back(directory + str.C_Str());
							break;
						case aiTextureType_HEIGHT:
							material.NormalMaps.push_back(directory + str.C_Str());
							break;
						case aiTextureType_NORMALS:
							material.NormalMaps.push_back(directory + str.C_Str());
							break;
					}
				}
			}
			// Necessary maps
			if (material.DiffuseMaps.size() == 0) {
				material.DiffuseMaps.push_back(Texture2D(glm::vec4(1.0f)));
			}
			if (material.SpecularMaps.size() == 0) {
				material.SpecularMaps.push_back(Texture2D(glm::vec4(1.0f)));
			}

			float shininess;
			if (AI_SUCCESS != aiGetMaterialFloat(mat, AI_MATKEY_SHININESS, &shininess))
			{
				material.Shininess = shininess;
			}

			return material;
		}
	}

}