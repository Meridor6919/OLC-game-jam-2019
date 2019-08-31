#include "Game.h"



Game::Game(std::shared_ptr<DirectX::SpriteBatch> sprite_batch, ID3D11Device *device)
{
	const int width = 185;
	const int height = 250;
	stickman_run_right = new MeridorGraphics::AnimatedSprite(sprite_batch.get(), { 0, 0, width, 250 }, -100, -100, 50, 50, 20.0f);
	stickman_run_right->AddTexture(L"s.png", device);
	for (int i = 0; i < 6; ++i)
	{
		stickman_run_right->AddFrame({ width + width * i, 0, 2*width + width * i, 250 });
	}
	
}

void Game::DrawPrimitiveBatch(DirectX::PrimitiveBatch<DirectX::VertexPositionColor> *primitive_batch, float delta_time)
{
	
	primitive_batch->Begin();

	DirectX::SimpleMath::Vector3 v1(0.f, 0.f, 0.0f);
	DirectX::SimpleMath::Vector3 v2(1200.f, 800.f, 0.f);

	DirectX::VertexPositionColor vc1(v1, DirectX::Colors::Black);
	DirectX::VertexPositionColor vc2(v2, DirectX::Colors::Black);

	primitive_batch->DrawLine(vc1, vc2);
	primitive_batch->End();
	
}

void Game::DrawSpriteBatch(DirectX::SpriteBatch * sprite_batch, float delta_time)
{
	
	sprite_batch->Begin();
	for (int j = 0; j < 16; ++j)
	{
		for (int i = 0; i < 24; ++i)
		{
			stickman_run_right->SetX(0 + i * 50);
			stickman_run_right->SetY(0 + j * 50);
			stickman_run_right->SetEffect(i > 12 ? DirectX::SpriteEffects::SpriteEffects_FlipHorizontally : DirectX::SpriteEffects::SpriteEffects_None);
			stickman_run_right->Draw(delta_time);
		}
	}
	sprite_batch->End();
	
}

