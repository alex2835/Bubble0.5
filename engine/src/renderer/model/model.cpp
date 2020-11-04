
#include "model.h"


namespace Bubble
{

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