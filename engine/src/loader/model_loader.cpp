
#include "loader.h"
#include "assimp/Importer.hpp"
#include "assimp/Exporter.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace Bubble
{
	void ProcessNode(Model& model, aiNode* node, const aiScene* scene, Loader* loader, const std::string& path);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, Loader* loader, const std::string& path);
	DefaultMaterial LoadMaterialTextures(aiMaterial* mat, Loader* loader, const std::string& path);

	Ref<Model> Loader::LoadModel(std::string path)
	{
        if (mLoadedModels.count(path))
        {
            return mLoadedModels[path];
        }

		auto model = CreateRef<Model>();
		mLoadedModels.emplace(path, model);

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, 0);
		
		if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode)
			throw std::runtime_error("ERROR::ASSIMP\n" + std::string(importer.GetErrorString()));

		importer.ApplyPostProcessing(aiProcess_Triangulate |
			aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenNormals);

		// Process ASSIMP's root node recursively
		model->mMeshes.reserve(scene->mNumMeshes);
		ProcessNode(*model, scene->mRootNode, scene, this, path);

		model->CreateBoundingBox();
		model->mShader = LoadShader("Phong shader");
		return model;
	}

	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void ProcessNode(Model& model, aiNode* node, const aiScene* scene, Loader* loader, const std::string& path)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			model.mMeshes.emplace_back(ProcessMesh(mesh, scene, loader, path));
		}
	
		for (int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(model, node->mChildren[i], scene, loader, path);
		}
	}
	
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, Loader* loader, const std::string& path)
	{
		VertexData vertices;
		std::vector<uint32_t> indices;
	
		vertices.mPositions.resize(mesh->mNumVertices);
		vertices.mNormals.resize(mesh->mNumVertices);
		vertices.mTexCoords.resize(mesh->mNumVertices);
		indices.reserve(mesh->mNumFaces);

		if (mesh->HasTangentsAndBitangents())
		{
			vertices.mTangents.resize(mesh->mNumVertices);
			vertices.mBitangents.resize(mesh->mNumVertices);
		}

		// Texture coordinates
		if (mesh->mTextureCoords[0])
		{
			for (int i = 0; i < mesh->mNumVertices; i++)
			{
				vertices.mTexCoords[i].x = mesh->mTextureCoords[0][i].x;
				vertices.mTexCoords[i].y = mesh->mTextureCoords[0][i].y;
			}
		}

		// Faces
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		memmove(vertices.mPositions.data(),  mesh->mVertices,   sizeof(glm::vec3) * vertices.mPositions.size());
		memmove(vertices.mNormals.data(),    mesh->mNormals,	sizeof(glm::vec3) * vertices.mNormals.size());
		memmove(vertices.mTangents.data(),   mesh->mTangents,   sizeof(glm::vec3) * vertices.mTangents.size());
		memmove(vertices.mBitangents.data(), mesh->mBitangents, sizeof(glm::vec3) * vertices.mBitangents.size());

		// Process materials
		aiMaterial* assimp_material = scene->mMaterials[mesh->mMaterialIndex];
		DefaultMaterial material = LoadMaterialTextures(assimp_material, loader, path);

		return Mesh(mesh->mName.C_Str(), std::move(material), std::move(vertices), std::move(indices));
	}
	
	// checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	DefaultMaterial LoadMaterialTextures(aiMaterial* mat, Loader* loader, const std::string& path)
	{
		const aiTextureType types[] = { aiTextureType_DIFFUSE , aiTextureType_SPECULAR, aiTextureType_HEIGHT, aiTextureType_NORMALS };
		
		// retrieve the directory path of the filepath
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
							material.mDiffuseMap = loader->LoadTexture2D(directory + str.C_Str());
							break;

						case aiTextureType_SPECULAR:
							material.mSpecularMap = loader->LoadTexture2D(directory + str.C_Str());
							break;

						//case aiTextureType_NORMALS:
						//	material.Normal = Texture2D(directory + str.C_Str());
						//	break;

						case aiTextureType_HEIGHT:
							material.mNormalMap = loader->LoadTexture2D(directory + str.C_Str());
							break;

						default:
							LOG_CORE_WARN("Model: {0} | Does't use texture: {1}", path, str.C_Str());
					}
				}
			}

			// Load material coefficients
			aiColor4D diffuse;
            ai_real specular[3];
            ai_real ambient[3];
            ai_real shininess;

			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
			{
				material.mDiffuseColor = *(glm::vec4*)&diffuse;
			}
			if (AI_SUCCESS == aiGetMaterialFloat(mat, AI_MATKEY_COLOR_SPECULAR, specular))
			{
				material.mSpecularCoef = *(float*)specular;
			}
            if (AI_SUCCESS == aiGetMaterialFloat(mat, AI_MATKEY_COLOR_AMBIENT, ambient))
            {
				material.mAmbientCoef = *(float*)ambient;
            }
			if (AI_SUCCESS == aiGetMaterialFloat(mat, AI_MATKEY_SHININESS, &shininess))
			{
				if (shininess)
				{
					material.mShininess = shininess;
				}
			}

			// In no textures create 1x1 white one
			Ref<Texture2D> white_plug = loader->LoadTexture2DSingleColor("white plug", glm::vec4(1.0f));
			if (!material.mDiffuseMap)
			{
				material.mDiffuseMap = white_plug;
			}
            if (!material.mSpecularMap)
            {
                material.mSpecularMap = white_plug;
            }

			return material;
		}
	}

}