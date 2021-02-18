
#include "model.h"
#include "loader.h"

namespace Bubble
{
	Model::Model() 
		: mRootNode("RootNode")
	{}

	void Model::CreateBoundingBox()
	{
		for (const auto& mesh : mMeshes)
		{
			const auto& vertices = mesh.mVertices;
			for (int i = 0; i < vertices.mPositions.size(); i++)
			{
				mBoundingBox.extend(vertices.mPositions[i]);
			}
		}
	}

}