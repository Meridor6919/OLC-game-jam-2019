#pragma once
#include "Animation.h"

class StickmanAnimationStay : public Animation
{

public:
	StickmanAnimationStay(DirectX::SpriteBatch* sprite_batch, ID3D11Device* device)
	{
		frame_time = 0.2f;
		path = L"Graphics\\StickmanStay.png";
		frame_width = 250;
		frame_height = 250;
		number_of_frames = 1;
		Animation::Init(sprite_batch, device);
	}
	void Draw(int x, int y, int width, int height, float depth, DirectX::SpriteEffects effect) { Animation::Draw(x, y, width, height, depth, effect); }
	bool LastFrameReached() { return Animation::LastFrameReached(); }
	void Update(float delta_time) { return Animation::Update(delta_time); }
};

