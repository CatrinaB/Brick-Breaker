#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace DrawCircle
{	
	Mesh* CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color);
}