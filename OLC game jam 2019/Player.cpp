#include "Player.h"





Player::Player(std::shared_ptr<StickmanAnimationLR> stickman_animation_left_right, std::shared_ptr<StickmanAnimation0> stickman_animation_zero)
{
	pos_x = 600;
	pos_y = 400;
	width = 100;
	height = 100;
	to_the_left = false;
	this->stickman_animation_left_right = stickman_animation_left_right;
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
	to_the_left = direction.x < 0;
	}
}

void Player::Draw()
{
	if (move)
	{
		stickman_animation_left_right->Draw(pos_x, pos_y, width, height, 1.0f, to_the_left ? DirectX::SpriteEffects::SpriteEffects_FlipHorizontally : DirectX::SpriteEffects::SpriteEffects_None);
	}
	else
	{
		stickman_animation_zero->Draw(pos_x, pos_y, width, height, 1.0f, to_the_left ? DirectX::SpriteEffects::SpriteEffects_FlipHorizontally : DirectX::SpriteEffects::SpriteEffects_None);
	}
}

void Player::Update(float delta_time)
{
	if (move)
	{

	stickman_animation_left_right->Update(delta_time);
	}
	else
	{
	stickman_animation_zero->Update(delta_time);

	}
}

