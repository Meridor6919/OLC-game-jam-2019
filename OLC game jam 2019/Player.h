#pragma once
#include "AnimationHeaders.h"

class Player
{
protected:

	float pos_x;
	float pos_y;
	int width;
	int height;
	float base_speed;
	bool to_the_left;
	bool firing = false;
	float fire_delay = 0.1f;
	float next_fire = 0.1f;
	bool move;
	std::tuple< std::shared_ptr<Animation>, float, int> moving;
	std::tuple< std::shared_ptr<Animation>, float, int> staying;
	virtual void SetBoundries();

public:
	Player(std::shared_ptr<Animation> moving, std::shared_ptr<Animation> staying);
	virtual void Move(DirectX::SimpleMath::Vector2 direction, float delta_time);
	virtual void Draw();
	virtual void Update(float delta_time);
	virtual float GetX() { return pos_x;  }
	virtual float GetY() { return pos_y; }
	virtual float GetWidth() { return static_cast<float>(width);  }
	virtual float GetHeight() { return static_cast<float>(height); }
	virtual bool Fire(float delta_time, bool to_the_left);
};

