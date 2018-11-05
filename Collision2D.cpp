#include "Collision2D.h"
#include "Brick.h"
#include "DrawRect.h"
#include <iostream>
#include <vector>
#include <include/glm.h>
#include <Component/SimpleScene.h>

#include <Core/Engine.h>

short Collision2D::WallCollision(glm::vec3 center, float walls[3], bool shield)
{
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
	if ((center[1] <= 5 && center[0] >= (platfx - platflength/2)) && (center[0] <= (platfx + platflength/2)))
		return 1;
	return 0;
}

short Collision2D::BlockCollision(glm::vec3 center, Brick brick)
{
	if (brick.level != 0)
	{
		if (center[0] + 10 >= brick.x_left_coord && center[0] + 10 <= brick.x_left_coord &&
			center[1] >= brick.y_lower_coord && center[1] <= brick.y_upper_coord)
			return 1;	//if the ball hits the brick from the left

		if (center[0] - 10 <= brick.x_right_coord &&  center[0] - 10 >= brick.x_left_coord &&
			center[1] >= brick.y_lower_coord && center[1] <= brick.y_upper_coord)
			return 2;	//if the ball hits the brick from the right

		if (center[1] + 10 >= brick.y_lower_coord && center[1] + 10 <= brick.y_upper_coord &&
			center[0] >= brick.x_left_coord && center[0] <= brick.x_right_coord)
			return 3;	//if the ball hits the brick from below


		if (center[1] - 10 <= brick.y_upper_coord && center[1] - 10 >= brick.y_lower_coord &&
			center[0] >= brick.x_left_coord && center[0] <= brick.x_right_coord)
			return 4;	//if the ball hits the brick from above
	}
	return 0;
}
