#include "Player.h"





void Player::SetBoundries()
{
	if (pos_x < 0)
		pos_x = 0;
	else if (pos_x > 1200 - width)
		pos_x = 1200 - width;
	if (pos_y < 50)
		pos_y = 50;
	else if (pos_y > 800 - height)
		pos_y = 800 - height;
}

Player::Player(std::shared_ptr<Animation> moving, std::shared_ptr<Animation> staying)
{
	pos_x = 600;
	pos_y = 400;
	width = 50;
	height = 50;
	to_the_left = false;
	this->moving = { moving, moving->FrameTime(), 0 };
	this->staying = { staying, staying->FrameTime(), 0 };
	base_speed = 200.0f;
	move = false;
}

void Player::Move(DirectX::SimpleMath::Vector2 direction, float delta_time)
{
	if (!direction.x && !direction.y)
	{
		move = false;
	}
	else 
	{
		move = true;
		float modifier = sqrt(1 / (direction.x*direction.x + direction.y * direction.y));
		direction.x *= modifier;
		direction.y *= modifier;
		pos_x += direction.x*base_speed*delta_time;
		pos_y -= direction.y*delta_time*base_speed;

		SetBoundries();
		if (!firing)
		{
			to_the_left = direction.x < 0;
		}
	}
}

void Player::Draw()
{
	if (firing)
	{
		firing = false;
		std::get<2>(moving) = 0;
		std::get<0>(moving)->Draw(pos_x, pos_y, width, height, 1.0f, to_the_left ? DirectX::SpriteEffects::SpriteEffects_FlipHorizontally : DirectX::SpriteEffects::SpriteEffects_None);
	}
	else if (move)
	{
		std::get<2>(staying) = 0;
		std::get<0>(moving)->SetFrame(std::get<2>(moving));
		std::get<0>(moving)->Draw(pos_x, pos_y, width, height, 1.0f, to_the_left ? DirectX::SpriteEffects::SpriteEffects_FlipHorizontally : DirectX::SpriteEffects::SpriteEffects_None);
	}
	else
	{
		std::get<2>(moving) = 0;
		std::get<0>(staying)->SetFrame(std::get<2>(staying));
		std::get<0>(staying)->Draw(pos_x, pos_y, width, height, 1.0f, to_the_left ? DirectX::SpriteEffects::SpriteEffects_FlipHorizontally : DirectX::SpriteEffects::SpriteEffects_None);
	}
}

void Player::Update(float delta_time)
{
	if (move)
	{
		std::get<1>(moving) -= delta_time;

		if (std::get<1>(moving) < 0)
		{
			std::get<1>(moving) = std::get<1>(moving) + std::get<0>(moving)->FrameTime();
			std::get<2>(moving) = (std::get<2>(moving) + 1) % (std::get<0>(moving)->NumberOfFrames() + 1) + 1;
			if (std::get<1>(moving) < 0)
				std::get<1>(moving) = 0;
		}
	}
	else
	{
		std::get<1>(staying) -= delta_time;

		if (std::get<1>(staying) < 0)
		{
			std::get<1>(staying) = std::get<1>(staying) + std::get<0>(staying)->FrameTime();
			std::get<2>(staying) = (std::get<2>(staying) + 1) % (std::get<0>(staying)->NumberOfFrames() + 1) + 1;
			if (std::get<1>(staying) < 0)
				std::get<1>(staying) = 0;
		}
	}
}

bool Player::Fire(float delta_time, bool to_the_left)
{
	firing = true;
	this->to_the_left = to_the_left;
	next_fire -= delta_time;
	if (next_fire < 0)
	{
		next_fire = fire_delay;
		return true;
	}
	else
	{
		return false;
	}
}

