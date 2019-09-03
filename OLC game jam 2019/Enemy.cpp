#include "Enemy.h"

Enemy::Enemy(std::shared_ptr<Animation> moving, std::shared_ptr<Animation> staying) : Player(moving, staying)
{
	int dir = rand() % 3;
	if (dir == 2)
	{
		pos_x = -100 + rand() % 1400;
		pos_y = 800 + rand() % 75;
	}
	else
	{
		pos_y = 50 + rand() % 850;
		if (dir == 1)
		{
			pos_x = -rand()%75;
		}
		else
		{
			pos_x = 1200 + rand() % 75;
		}
	}
	width = 50;
	height = 50;
	to_the_left = false;
	this->moving = { moving, moving->FrameTime(), 0 };
	this->staying = { staying, staying->FrameTime(), 0 };
	base_speed = 190.0f;
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

