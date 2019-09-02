#pragma once
#include "StickmanAnimationLR.h"
#include "StickmanAnimation0.h"

class Player
{
protected:

	float pos_x;
	float pos_y;
	int width;
	int height;
	float base_speed;
	bool to_the_left;
	bool move;
	std::tuple< std::shared_ptr<StickmanAnimationLR>, float, int> stickman_animation_left_right;
	std::shared_ptr<StickmanAnimation0> stickman_animation_zero;

public:
	Player(std::shared_ptr<StickmanAnimationLR> stickman_animation_left_right, std::shared_ptr<StickmanAnimation0> stickman_animation_zero);
	virtual void Move(DirectX::SimpleMath::Vector2 direction, float delta_time);
	virtual void Draw();
	virtual void Update(float delta_time);
	virtual float GetX() { return pos_x;  }
	virtual float GetY() { return pos_y; }
};

