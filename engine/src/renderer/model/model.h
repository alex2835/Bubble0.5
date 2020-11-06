#pragma once

#include "mesh.h"
#include "glm-aabb/AABB.hpp"

#include <vector>


namespace Bubble
{
	struct Model
	{
		std::vector<Mesh> mMeshes;
		Ref<Shader> mShader;
		AABB mBoundingBox;

		Model();
		
		Model(const Model&) = delete;
		Model& operator= (const Model&) = delete;

		Model(Model&&) = default;
		Model& operator= (Model&&) = default;

		void CreateBoundingBox();
	};

}