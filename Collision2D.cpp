#include "Collision2D.h"
#include <iostream>
#include <include/glm.h>

#include <Core/Engine.h>

struct brick {
	std::string name;
	float x_left_coord;
	float x_right_coord;
	float y_lower_coord;
	float y_upper_coord;
	short level;
};

short Collision2D::WallCollision(glm::vec3 center, float walls[3], bool shield)
{
	//std::cout << center[1] << "\nwall" << walls[1] << '\n';
	if (((center[0] - 10) <= walls[0] || (center[0] + 10) >= walls[2]) && (center[1] + 20) < walls[1])
		return 1;

	if (((center[0] - 10) > walls[0] || (center[0] + 10) < walls[2]) && (center[1] + 20) >= walls[1])
		return 2;
	
	if (center[1] < -10 && shield == false)
		return 3;

	if (center[1] < -10 && shield == true)
		return 4;

	return 0;
}

short Collision2D::PlatformCollision(glm::vec3 center, float platfx, float platflength)
{
	//std::cout << center[1] << ' ' << center[0] << ' ' << (platfx - platflength/2) << ' ' << (platfx + platflength/2) << '\n';
	if ((center[1] <= 5 && center[0] >= (platfx - platflength/2)) && (center[0] <= (platfx + platflength/2)))
		return 1;
	return 0;
}

//short Collision2D::BlockCollision(glm::vec3 center, std::vector <brick> blocks, float constx, float consty)
//{
//	for (int i = 0; i < 50; i++)
//	{
//		if (center[0] + 10 >= blocks.at(i)[0] && center[0] + 10 <= blocks.at(i)[1] && center[1] >= blocks.at(i)[2] && center[1] <= blocks.at(i)[3])
//			if (constx > 0)
//				return 1;
//			else
//				return 2;
//			
//	}
//	return 0;
//}