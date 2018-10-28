#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace DrawRect
{
	Mesh* CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float height, float width, glm::vec3 color, bool fill = false);
}