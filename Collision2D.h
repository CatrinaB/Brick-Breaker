#pragma once

#include <include/glm.h>

struct brick {
	std::string name;
	float x_left_coord;
	float x_right_coord;
	float y_lower_coord;
	float y_upper_coord;
	short level;
};

namespace Collision2D
{
	short WallCollision(glm::vec3 center, float walls[4], bool shield);
	short PlatformCollision(glm::vec3 center, float platfx, float platflength);
	//short BlockCollision(glm::vec3 center, std::vector <brick> blocks, float constx, float consty);
}