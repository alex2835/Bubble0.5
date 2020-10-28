
#include "model_loader.h"


namespace Bubble
{
	std::vector<std::pair<std::string, Ref<Model>>>  ModelLoader::LoadedModels;


	static std::string ReplaceAll(std::string str, const std::string& from, const std::string& to)
	{
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos)
		{
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
		}
		return str;
	}

	static std::string NormalizePath(const std::string& path)
	{
		return ReplaceAll(path, "\\", "/");
	}
	

	Ref<Model> ModelLoader::StaticModel(std::string path)
	{
		path = NormalizePath(path);

		for (const auto& stored_model : LoadedModels)
		{
			if (stored_model.first.find(path) != std::string::npos ||
				path.find(stored_model.first) != std::string::npos)
			{
				return stored_model.second;
			}
		}

		auto model = CreateRef<Model>();
		LoadedModels.push_back(std::make_pair(path, model));

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenNormals);
		
		if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode)
			throw std::runtime_error("ERROR::ASSIMP\n" + std::string(importer.GetErrorString()));

		// Process ASSIMP's root node recursively
		model->mMeshes.reserve(scene->mNumMeshes);
		ProcessNode(*model, scene->mRootNode, scene);

		model->CreateBoundBox();

		return model;
	}

	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void ModelLoader::ProcessNode(Model& model, aiNode* node, const aiScene* scene)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			model.mMeshes.emplace_back(ProcessMesh(mesh, scene));
		}
	
		for (int i = 0; i < node->mNumChildren; i++) {
			ProcessNode(model, node->mChildren[i], scene);
		}
	}
	
	Mesh ModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		VertexData vertices;
		std::vector<uint32_t> indices;
	
		vertices.Positions.resize(mesh->mNumVertices);
		vertices.Normals.resize(mesh->mNumVertices);
		vertices.TexCoords.resize(mesh->mNumVertices);
		indices.reserve(mesh->mNumFaces);

		if (mesh->HasTangentsAndBitangents())
		{
			vertices.Tangents.resize(mesh->mNumVertices);
			vertices.Bitangents.resize(mesh->mNumVertices);
		}

		// Texture coords
		if (mesh->mTextureCoords[0])
		{
			for (int i = 0; i < mesh->mNumVertices; i++)
			{
				vertices.TexCoords[i].x = mesh->mTextureCoords[0][i].x;
				vertices.TexCoords[i].y = mesh->mTextureCoords[0][i].y;
			}
		}

		// Faces
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		memmove(vertices.Positions.data(),  mesh->mVertices,	sizeof(glm::vec3) * vertices.Positions.size());
		memmove(vertices.Normals.data(),    mesh->mNormals,		sizeof(glm::vec3) * vertices.Normals.size());
		memmove(vertices.Tangents.data(),   mesh->mTangents,	sizeof(glm::vec3) * vertices.Tangents.size());
		memmove(vertices.Bitangents.data(), mesh->mBitangents,	sizeof(glm::vec3) * vertices.Bitangents.size());

		// Process materials
		aiMaterial* assimp_material = scene->mMaterials[mesh->mMaterialIndex];
		DefaultMaterial material = LoadMaterialTextures(assimp_material);

		return Mesh(std::move(material), std::move(vertices), std::move(indices));
	}
	
	// checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	DefaultMaterial ModelLoader::LoadMaterialTextures(aiMaterial* mat)
	{
		const aiTextureType types[] = { aiTextureType_DIFFUSE , aiTextureType_SPECULAR, aiTextureType_HEIGHT, aiTextureType_NORMALS };
		
		// retrieve the directory path of the filepath
		const std::string& path = LoadedModels.back().first;
		std::string directory = path.substr(0, path.find_last_of('/') + 1);



		DefaultMaterial material;
		for (int i = 0; i < 3; i++)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < mat->GetTextureCount(types[i]); j++)
				{
					aiString str;
					mat->GetTexture(types[i], j, &str);

					switch (types[i])
					{
						case aiTextureType_DIFFUSE:
							material.Diffuse = Texture2D(directory + str.C_Str());
							break;
						case aiTextureType_SPECULAR:
							material.Specular = Texture2D(directory + str.C_Str());
							break;
						case aiTextureType_NORMALS:
							material.Normal = Texture2D(directory + str.C_Str());
							break;
						//case aiTextureType_HEIGHT:
						//	material.Normal = Texture2D(directory + str.C_Str());
						//	break;
						default:
							LOG_CORE_WARN("Model: {0} | Does't use texture: {1}", LoadedModels.back().first, str.C_Str());
					}
				}
			}

			// Necessary maps
			if (material.Diffuse.GetHeight() == 0)
				material.Diffuse = Texture2D(Texture2D(glm::vec4(1.0f)));

			if (material.Specular.GetHeight() == 0)
				material.Specular = Texture2D(Texture2D(glm::vec4(1.0f)));
			
			float shininess;
			if (AI_SUCCESS != aiGetMaterialFloat(mat, AI_MATKEY_SHININESS, &shininess))
			{
				material.Shininess = shininess;
			}

			return material;
		}
	}

}