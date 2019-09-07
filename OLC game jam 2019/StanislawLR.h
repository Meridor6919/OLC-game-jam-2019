#pragma once
#include "Animation.h"

class StanislawLR : public Animation
{

public:
	StanislawLR(DirectX::SpriteBatch* sprite_batch, ID3D11Device* device)
	{
		frame_time = 0.04f;
		path = L"Graphics\\StanislawLR.png";
		frame_width = 160;
		frame_height = 160;
		number_of_frames = 1;
		Animation::Init(sprite_batch, device);
	}
	void Draw(int x, int y, int width, int height, float depth, DirectX::SpriteEffects effect) { Animation::Draw(x, y, width, height, depth, effect); }
	bool LastFrameReached() { return Animation::LastFrameReached(); }
	void Update(float delta_time) { return Animation::Update(delta_time); }
};

