#pragma once
#include <string>

class Brick
{

public:
	Brick() = default;

	Brick(std::string name, float xlc, float xrc, float ylc, float yuc, short l) :name{ name }, x_left_coord{ xlc },
		x_right_coord{ xrc }, y_lower_coord{ ylc }, y_upper_coord{ yuc }, level{ l }{}

	~Brick() = default;

	std::string name;
	float x_left_coord;
	float x_right_coord;
	float y_lower_coord;
	float y_upper_coord;
	short level;
};