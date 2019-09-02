#include "Enemy.h"

Enemy::Enemy(std::shared_ptr<StickmanAnimationLR> stickman_animation_left_right, std::shared_ptr<StickmanAnimation0> stickman_animation_zero) : Player(stickman_animation_left_right, stickman_animation_zero)
{
	pos_x = 0 + rand()%1200;
	pos_y = 0;
	width = 50;
	height = 50;
	to_the_left = false;
	this->stickman_animation_left_right = { stickman_animation_left_right, stickman_animation_left_right->FrameTime(), 0 };
	this->stickman_animation_zero = stickman_animation_zero;
	base_speed = 50.0f;
	move = false;
}


