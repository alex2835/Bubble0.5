#pragma once

#include "mesh.h"
#include "glm-aabb/AABB.hpp"

#include <vector>


namespace Bubble
{
	struct MeshNode
	{
		std::string mName;
		std::vector<Mesh*> mMeshes;
		std::vector<Scope<MeshNode>> mChildern;

		inline MeshNode(const std::string& name)
			: mName(name)
		{}
	};

	struct Model
	{
		std::vector<Mesh> mMeshes;
		Ref<Shader> mShader;
		AABB mBoundingBox;
		MeshNode mRootNode;

		Model();
		Model(const Model&) = delete;
		Model& operator= (const Model&) = delete;
		Model(Model&&) = default;
		Model& operator= (Model&&) = default;

		void CreateBoundingBox();
	};

}