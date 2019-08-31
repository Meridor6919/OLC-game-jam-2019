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
void MeridorGraphics::AnimatedSprite::Draw(float delta_time)
{
	MeridorGraphics::Sprite::Draw();
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

void MeridorGraphics::AnimatedSprite::SetFrameTime(float frame_time)
{
	this->frame_time = frame_time;
}
