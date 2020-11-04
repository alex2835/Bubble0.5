
#include "frustum_culling .h"


namespace Bubble
{
	glm::vec4 FrustumPlanes[6];

	
	void SetFrustumPlanes(const glm::mat4& view_proj)
	{
		// Left Frustum Plane
		// Add first column of the matrix to the fourth column
		FrustumPlanes[0].x = view_proj[0][3] + view_proj[0][0];
		FrustumPlanes[0].y = view_proj[1][3] + view_proj[1][0];
		FrustumPlanes[0].z = view_proj[2][3] + view_proj[2][0];
		FrustumPlanes[0].w = view_proj[3][3] + view_proj[3][0];

		// Right Frustum Plane
		// Subtract first column of matrix from the fourth column
		FrustumPlanes[0].x = view_proj[0][3] - view_proj[0][0];
		FrustumPlanes[0].y = view_proj[1][3] - view_proj[1][0];
		FrustumPlanes[0].z = view_proj[2][3] - view_proj[2][0];
		FrustumPlanes[0].w = view_proj[3][3] - view_proj[3][0];

		// Top Frustum Plane
		// Subtract second column of matrix from the fourth column
		FrustumPlanes[1].x = view_proj[0][3] - view_proj[0][1];
		FrustumPlanes[1].y = view_proj[1][3] - view_proj[1][1];
		FrustumPlanes[1].z = view_proj[2][3] - view_proj[2][1];
		FrustumPlanes[1].w = view_proj[3][3] - view_proj[3][1];

		// Bottom Frustum Plane
		// Add second column of the matrix to the fourth column
		FrustumPlanes[2].x = view_proj[0][3] + view_proj[0][1];
		FrustumPlanes[2].y = view_proj[1][3] + view_proj[1][1];
		FrustumPlanes[2].z = view_proj[2][3] + view_proj[2][1];
		FrustumPlanes[2].w = view_proj[3][3] + view_proj[3][1];

		// Near Frustum Plane
		// We could add the third column to the fourth column to get the near plane,
		// but we don't have to do this because the third column IS the near plane
		FrustumPlanes[3].x = view_proj[0][2];
		FrustumPlanes[3].y = view_proj[1][2];
		FrustumPlanes[3].z = view_proj[2][2];
		FrustumPlanes[3].w = view_proj[3][2];

		// Far Frustum Plane
		// Subtract third column of matrix from the fourth column
		FrustumPlanes[5].x = view_proj[0][3] - view_proj[0][2];
		FrustumPlanes[5].y = view_proj[1][3] - view_proj[1][2];
		FrustumPlanes[5].z = view_proj[2][3] - view_proj[2][2];
		FrustumPlanes[5].w = view_proj[3][3] - view_proj[3][2];

		for (int i = 0; i < 6; i++)
		{
			float length = sqrt((FrustumPlanes[i].x * FrustumPlanes[i].x) + (FrustumPlanes[i].y * FrustumPlanes[i].y) + (FrustumPlanes[i].z * FrustumPlanes[i].z));
			FrustumPlanes[i].x /= length;
			FrustumPlanes[i].y /= length;
			FrustumPlanes[i].z /= length;
			FrustumPlanes[i].w /= length;
		}

	}


	bool IsInFrustum(const AABB& bb)
	{
		const glm::vec3& min = bb.getMin();
		const glm::vec3& max = bb.getMax();

		for (int planeID = 0; planeID < 6; planeID++)
		{
			glm::vec3 axis_vert;

			// x-axis
			if (FrustumPlanes[planeID].x < 0.0f) {    // Which AABB vertex is furthest down (plane normals direction) the x axis
				axis_vert.x = min.x;
			}
			else {
				axis_vert.x = max.x;
			}

			// y-axis
			if (FrustumPlanes[planeID].y < 0.0f) {    // Which AABB vertex is furthest down (plane normals direction) the y axis
				axis_vert.y = min.y;
			}
			else {
				axis_vert.y = max.y;
			}

			// z-axis
			if (FrustumPlanes[planeID].z < 0.0f) {   // Which AABB vertex is furthest down (plane normals direction) the z axis
				axis_vert.z = min.z;
			}
			else {
				axis_vert.z = max.z;
			}


			glm::vec3 plane_normal = FrustumPlanes[planeID].xyz;
			float plane_Constant = FrustumPlanes[planeID].w;

			// Outside the frustum
			if (glm::dot(plane_normal, axis_vert) + plane_Constant < 0.0f)
			{
				return false;
			}
		}

		return true;
	}

}