
#include "model.h"


namespace Bubble
{

	void Model::CreateBoundBox()
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

	AABB Model::RecalculateBoundingBox(glm::mat4 transform)
	{
		return AABB();
	}

}