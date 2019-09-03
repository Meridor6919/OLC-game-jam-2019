#pragma once
#include "Sprite.h"
#include <vector>

namespace MeridorGraphics {

	class AnimatedSprite : public Sprite {

		float time_to_next_frame;
		std::vector<RECT> frames;
		float frame_time;
		int frame_index;
		bool last_frame_reached;

	public:

		AnimatedSprite(DirectX::SpriteBatch* sprite_batch, RECT source, LONG pos_x, LONG pos_y, LONG width, LONG height, float frame_time, float depth = 0.0f, float rotation = 0.0f);
		void AddFrame(RECT frame);
		void Draw();
		void SetFrameTime(float frame_time);
		void SetFrame(int frame);
		void Update(float delta_time);
		bool EndReached();

	};
}