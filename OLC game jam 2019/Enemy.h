#pragma once
#include "Player.h"
class Enemy : public Player
{
protected:
	void SetBoundries() { return; }
public:
	Enemy(std::shared_ptr<Animation> moving, std::shared_ptr<Animation> staying);
	bool Hit();
};

