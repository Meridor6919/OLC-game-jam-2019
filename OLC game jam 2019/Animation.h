#pragma once
#include <string>
#include "DirectXApplication.h"
#include "SimpleMath.h"
#include "PrimitiveBatch.h"
#include "VertexTypes.h"
#include "AnimatedSprite.h"

class Animation {

public:
	float frame_time;
	std::wstring path;
	int frame_width;
	int frame_height;
	int number_of_frames;
	std::unique_ptr<MeridorGraphics::AnimatedSprite> animated_sprite;

	void Init(DirectX::SpriteBatch* sprite_batch, ID3D11Device* device)
	{
		RECT r = { 0,0,frame_width, frame_height };
		animated_sprite = std::make_unique<MeridorGraphics::AnimatedSprite>(sprite_batch, r, 0, 0, 0, 0, frame_time);
		animated_sprite->AddTexture(path.c_str(), device);
		for (int i = 0; i < number_of_frames - 1; ++i)
		{
			animated_sprite->AddFrame({ 0, frame_height + frame_height * i, frame_width, frame_height * 2 + frame_height * i });
		}
	}
	virtual void Draw(int x, int y, int width, int height, float depth, DirectX::SpriteEffects effect) 
	{ 
		animated_sprite->SetEffect(effect);
		animated_sprite->SetY(y);
		animated_sprite->SetX(x);
		animated_sprite->SetWidth(width);
		animated_sprite->SetHeight(height);
		animated_sprite->SetDepth(depth);
		animated_sprite->Draw(); 
	}
	virtual bool LastFrameReached() 
	{
		return animated_sprite->EndReached();
	}
	virtual void Update(float delta_time)
	{
		
	}
public:
	virtual int NumberOfFrames()
	{
		return number_of_frames;
	}
	virtual float FrameTime()
	{
		return frame_time;
	}
	virtual void SetFrame(int frame)
	{
		animated_sprite->SetFrame(frame);
	}
};