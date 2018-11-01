#pragma once

#include <include/glm.h>
#include "Brick.h"
#include <vector>

namespace Collision2D
{
	short WallCollision(glm::vec3 center, float walls[4], bool shield);
	short PlatformCollision(glm::vec3 center, float platfx, float platflength);
	short BlockCollision(glm::vec3 center,  Brick brick);
}