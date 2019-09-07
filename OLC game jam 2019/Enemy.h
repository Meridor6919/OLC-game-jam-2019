#pragma once
#include "Player.h"
class Enemy : public Player
{
protected:
	void SetBoundries() { return; }
	std::tuple< std::shared_ptr<Animation>, float, int> dying;
	bool dead = false;
	
public:
	bool falling = false;
	Enemy(std::shared_ptr<Animation> moving, std::shared_ptr<Animation> staying, std::shared_ptr<Animation> dying);
	bool Hit();
	void Move(DirectX::SimpleMath::Vector2 direction, float delta_time);
	void Draw();
	void Update(float delta_time);
	bool Remove();
};

