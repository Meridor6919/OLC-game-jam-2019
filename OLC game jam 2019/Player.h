#pragma once
#include "StickmanAnimationLR.h"
#include "StickmanAnimation0.h"

class Player
{
	float pos_x;
	float pos_y;
	int width;
	int height;
	float base_speed;
	bool to_the_left;
	bool move;
	std::shared_ptr<StickmanAnimationLR> stickman_animation_left_right;
	std::shared_ptr<StickmanAnimation0> stickman_animation_zero;

public:
	Player(std::shared_ptr<StickmanAnimationLR> stickman_animation_left_right, std::shared_ptr<StickmanAnimation0> stickman_animation_zero);
	void Move(DirectX::SimpleMath::Vector2 direction, float delta_time);
	void Draw();
	void Update(float delta_time);
};

