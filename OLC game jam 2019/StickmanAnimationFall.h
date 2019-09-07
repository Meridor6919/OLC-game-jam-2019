#pragma once
#include "Animation.h"

class StickmanAnimationFall : public Animation
{

public:
	StickmanAnimationFall(DirectX::SpriteBatch* sprite_batch, ID3D11Device* device)
	{
		frame_time = 0.05f;
		path = L"Graphics\\StickmanFall.png";
		frame_width = 250;
		frame_height = 250;
		number_of_frames = 8;
		Animation::Init(sprite_batch, device);
	}
	void Draw(int x, int y, int width, int height, float depth, DirectX::SpriteEffects effect) { Animation::Draw(x, y, width, height, depth, effect); }
	bool LastFrameReached() { return Animation::LastFrameReached(); }
	void Update(float delta_time) { return Animation::Update(delta_time); }
};

