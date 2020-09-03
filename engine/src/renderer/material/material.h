#pragma once

#include "glm/glm.hpp"


namespace Bubble
{
	struct BaseMaterial {
		glm::vec3 Ambient;
		glm::vec3 Diffuse;
		glm::vec3 Specular;
		int Shininess;

		BaseMaterial(const glm::vec3& ambient,
					 const glm::vec3& diffuse,
					 const glm::vec3& specular,
					 int Shininess = 32);
	};
}