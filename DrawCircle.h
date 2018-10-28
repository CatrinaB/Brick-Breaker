#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace DrawCircle
{	
	Mesh* CreateCircle(std::string name, float radius, float coordx, float coordy, glm::vec3 color);
}