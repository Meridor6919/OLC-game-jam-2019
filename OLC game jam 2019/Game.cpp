#include "Game.h"



Game::Game(DirectX::SpriteBatch* sprite_batch, ID3D11Device* device)
{
	stickman_animation_left_right = std::make_unique<StickmanAnimationLR>(sprite_batch, device);
}

void Game::DrawPrimitiveBatch(DirectX::PrimitiveBatch<DirectX::VertexPositionColor> *primitive_batch, float delta_time)
{
	
	primitive_batch->Begin();

	DirectX::SimpleMath::Vector3 v1(900.f, 0.f, 0.0f);
	DirectX::SimpleMath::Vector3 v2(900.f, 800.f, 0.f);

	DirectX::VertexPositionColor vc1(v1, DirectX::Colors::Black);
	DirectX::VertexPositionColor vc2(v2, DirectX::Colors::Black);

	primitive_batch->DrawLine(vc1, vc2);
	primitive_batch->End();
	
}

void Game::DrawSpriteBatch(DirectX::SpriteBatch * sprite_batch, float delta_time)
{
	static int distance = 0;
	distance++;
	sprite_batch->Begin();
	
	for (int j = 0; j < 32; ++j)
	{
		for (int i = 0; i < 24; ++i)
		{
			stickman_animation_left_right->Draw(i * 25 + distance, j * 25, 50, 50, 0.0f, DirectX::SpriteEffects::SpriteEffects_None);
		}
	}
	stickman_animation_left_right->Update(delta_time);
	sprite_batch->End();
	
}

