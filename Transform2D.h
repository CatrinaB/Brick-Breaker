#pragma once

#include <include/glm.h>

namespace Transform2D
{
	inline glm::mat3 Translate(float translateX, float translateY)
	{
		return glm::transpose(
			glm::mat3(
				1, 0, translateX,
				0, 1, translateY,
				0, 0, 1
			)
		);
	}
}