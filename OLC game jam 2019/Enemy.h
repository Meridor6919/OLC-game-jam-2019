#pragma once
#include "Player.h"
class Enemy : public Player
{


public:
	Enemy(std::shared_ptr<StickmanAnimationLR> stickman_animation_left_right, std::shared_ptr<StickmanAnimation0> stickman_animation_zero);
	void Move(DirectX::SimpleMath::Vector2 direction, float delta_time);
	void Draw();
	void Update(float delta_time);
};

