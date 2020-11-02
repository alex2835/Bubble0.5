
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
		glm::vec3 min = mBoundingBox.getMin();
		glm::vec3 max = mBoundingBox.getMax();

		glm::vec3 pos[] = { min, max,
			glm::vec3(max.x, min.y, min.z),
			glm::vec3(min.x, max.y, min.z),
			glm::vec3(min.x, min.y, max.z),
			glm::vec3(max.x, max.y, min.z),
			glm::vec3(min.x, max.y, max.z),
			glm::vec3(max.x, min.y, max.z)
		};

		AABB new_bb;
		for (int i = 0; i < 8; i++)
		{
			new_bb.extend(transform * glm::vec4(pos[i].xyz, 1));
		}
		return new_bb;
	}

}