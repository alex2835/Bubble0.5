
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

	AABB Model::TransformBoundingBox(const glm::mat4& transform)
	{
		glm::vec3 min = transform * glm::vec4(mBoundingBox.getMin().xyz, 1);
		glm::vec3 max = transform * glm::vec4(mBoundingBox.getMax().xyz, 1);
		return AABB(min, max);
	}

}