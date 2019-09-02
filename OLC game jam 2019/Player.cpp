#include "Player.h"





Player::Player(std::shared_ptr<StickmanAnimationLR> stickman_animation_left_right, std::shared_ptr<StickmanAnimation0> stickman_animation_zero)
{
	pos_x = 600;
	pos_y = 400;
	width = 100;
	height = 100;
	to_the_left = false;
	this->stickman_animation_left_right = { stickman_animation_left_right, stickman_animation_left_right->FrameTime(), 0 };
	this->stickman_animation_zero = stickman_animation_zero;
	base_speed = 200.0f;
	move = false;
}

void Player::Move(DirectX::SimpleMath::Vector2 direction, float delta_time)
{
	if (!direction.x && !direction.y)
	{
		move = false;
	}
	else {
		move = true;
	pos_x += direction.x*base_speed*delta_time;
	pos_y -= direction.y*delta_time*base_speed;

	if (pos_x < 0)
		pos_x = 0;
	else if (pos_x > 1200 - width)
		pos_x = 1200 - width;
	if (pos_y < 0)
		pos_y = 0;
	else if (pos_y > 800 - height)
		pos_y = 800 - height;
	
	to_the_left = direction.x < 0;
	}
}

void Player::Draw()
{
	if (move)
	{
		std::get<0>(stickman_animation_left_right)->SetFrame(std::get<2>(stickman_animation_left_right));
		std::get<0>(stickman_animation_left_right)->Draw(pos_x, pos_y, width, height, 1.0f, to_the_left ? DirectX::SpriteEffects::SpriteEffects_FlipHorizontally : DirectX::SpriteEffects::SpriteEffects_None);
	}
	else
	{
		std::get<2>(stickman_animation_left_right) = 0;
		stickman_animation_zero->Draw(pos_x, pos_y, width, height, 1.0f, to_the_left ? DirectX::SpriteEffects::SpriteEffects_FlipHorizontally : DirectX::SpriteEffects::SpriteEffects_None);
	}
}

void Player::Update(float delta_time)
{
	if (move)
	{
		std::get<1>(stickman_animation_left_right) -= delta_time;

		if (std::get<1>(stickman_animation_left_right) < 0)
		{
			std::get<1>(stickman_animation_left_right) = std::get<1>(stickman_animation_left_right) + std::get<0>(stickman_animation_left_right)->FrameTime();
			std::get<2>(stickman_animation_left_right) = (std::get<2>(stickman_animation_left_right) + 1) % (std::get<0>(stickman_animation_left_right)->NumberOfFrames() + 1) + 1;
			if (std::get<1>(stickman_animation_left_right) < 0)
				std::get<1>(stickman_animation_left_right) = 0;
		}
	}
	else
	{
	stickman_animation_zero->Update(delta_time);

	}
}

