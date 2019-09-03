#include "AnimatedSprite.h"

MeridorGraphics::AnimatedSprite::AnimatedSprite(DirectX::SpriteBatch * sprite_batch, RECT source, LONG pos_x, LONG pos_y, LONG width, LONG height, float frame_time, float depth, float rotation) : Sprite(sprite_batch, source, pos_x, pos_y, width, height, depth, rotation)
{
	this->frame_time = frame_time;
	time_to_next_frame = frame_time;
	frame_index = 0;
	frames.push_back(source);
	last_frame_reached = false;
}
void MeridorGraphics::AnimatedSprite::AddFrame(RECT frame)
{
	frames.push_back(frame);
}
void MeridorGraphics::AnimatedSprite::Draw()
{
	MeridorGraphics::Sprite::Draw();
}

void MeridorGraphics::AnimatedSprite::SetFrameTime(float frame_time)
{
	this->frame_time = frame_time;
}

void MeridorGraphics::AnimatedSprite::SetFrame(int frame)
{
	source = frames[frame % static_cast<int>(frames.size())];
}

void MeridorGraphics::AnimatedSprite::Update(float delta_time)
{
	time_to_next_frame -= delta_time;

	if (time_to_next_frame < 0)
	{
		time_to_next_frame = time_to_next_frame + frame_time;

		frame_index++;
		if (frame_index == frames.size())
		{
			last_frame_reached = true;
			frame_index = 0;
		}
		if (time_to_next_frame < 0)
			time_to_next_frame = 0;

		source = frames[frame_index];
	}
}

bool MeridorGraphics::AnimatedSprite::EndReached()
{
	if(last_frame_reached)
	{ 
		last_frame_reached = false; 
		return true; 
	}
	else
	{
		return false;
	}
}
