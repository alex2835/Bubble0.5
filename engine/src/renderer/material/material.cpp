
#include "material.h"


namespace Bubble
{

	BaseMaterial::BaseMaterial(const glm::vec3& ambient,
							   const glm::vec3& diffuse,
							   const glm::vec3& specular,
							   int Shininess)
		: Ambient(ambient),
		  Diffuse(diffuse),
		  Specular(specular),
		  Shininess(Shininess)
	{}

}