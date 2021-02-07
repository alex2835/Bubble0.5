
#include "model.h"
#include "loader.h"

namespace Bubble
{
	Model::Model()
	{
		mShader = Loader::LoadShader("resources/shaders/phong.glsl");
	}

	void Model::CreateBoundingBox()
	{
		for (const auto& mesh : mMeshes)
		{
			const auto& vertices = mesh.mVertices;
			for (int i = 0; i < vertices.Positions.size(); i++)
			{
				mBoundingBox.extend(vertices.Positions[i]);
			}
		}
	}

}