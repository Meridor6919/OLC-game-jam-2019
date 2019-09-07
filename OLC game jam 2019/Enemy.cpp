#include "Enemy.h"

Enemy::Enemy(std::shared_ptr<Animation> moving, std::shared_ptr<Animation> staying, std::shared_ptr<Animation> dying) : Player(moving, staying)
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
	this->dying = { dying, dying->FrameTime(), 0 };
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

void Enemy::Move(DirectX::SimpleMath::Vector2 direction, float delta_time)
{
	if (!falling)
		Player::Move(direction, delta_time);
}

void Enemy::Draw()
{
	if (!falling)
		Player::Draw();
	else
	{
		std::get<0>(dying)->SetFrame(std::get<2>(dying));
		std::get<0>(dying)->Draw(pos_x, pos_y, width, height, 1.0f, to_the_left ? DirectX::SpriteEffects::SpriteEffects_FlipHorizontally : DirectX::SpriteEffects::SpriteEffects_None);
	}
}

void Enemy::Update(float delta_time)
{
	if (!falling)
		Player::Update(delta_time);
	else
	{
		//pos_x += (to_the_left * 2 + 1)*delta_time*100.0f;
		//pos_y += delta_time*50.0f;

		std::get<1>(dying) -= delta_time;
		if (std::get<1>(dying) < 0)
		{
			std::get<1>(dying) = std::get<1>(dying) + std::get<0>(dying)->FrameTime();
			std::get<2>(dying) = (std::get<2>(dying) + 1) % (std::get<0>(dying)->NumberOfFrames() + 1) + 1;
			if (std::get<2>(dying) == 8)
				dead = true;
		}
	}
}

bool Enemy::Remove()
{
	return dead;
}

