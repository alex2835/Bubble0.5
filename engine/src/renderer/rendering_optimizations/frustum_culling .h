#pragma once

#include "glm-aabb/AABB.hpp"


namespace Bubble
{
	void SetFrustumPlanes(const glm::mat4& view_proj);
	bool IsInFrustum(const AABB& bb);
}