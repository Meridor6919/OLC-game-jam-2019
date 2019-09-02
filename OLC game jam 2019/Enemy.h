#pragma once
#include "Player.h"
class Enemy : public Player
{


public:
	Enemy(std::shared_ptr<StickmanAnimationLR> stickman_animation_left_right, std::shared_ptr<StickmanAnimation0> stickman_animation_zero);
};

