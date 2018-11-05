#pragma once
#include <string>

class Brick
{

public:
	Brick() = default;

	Brick(std::string name, short xlc, short xrc, short ylc, short yuc, short l, short pw) :name{ name }, x_left_coord{ xlc },
		x_right_coord{ xrc }, y_lower_coord{ ylc }, y_upper_coord{ yuc }, level{ l }, powerup{ pw }{}

	~Brick() = default;

	std::string name;
	short x_left_coord;
	short x_right_coord;
	short y_lower_coord;
	short y_upper_coord;
	short level;
	short powerup;
};