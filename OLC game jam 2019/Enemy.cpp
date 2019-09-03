#include "Enemy.h"

Enemy::Enemy(std::shared_ptr<Animation> moving, std::shared_ptr<Animation> staying) : Player(moving, staying)
{
	pos_x = 0 + rand()%1200;
	pos_y = 0;
	width = 50;
	height = 50;
	to_the_left = false;
	this->moving = { moving, moving->FrameTime(), 0 };
	this->staying = { staying, staying->FrameTime(), 0 };
	base_speed = 100.0f;
	move = false;
}

bool Enemy::Hit()
{
	if(std::get<2>(staying) == 12)
	{ 
		std::get<2>(staying) = 0;
		return true; 
	}
	return false;
}


