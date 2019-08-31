#include "Game.h"



Game::Game(std::shared_ptr<DirectX::SpriteBatch> sprite_batch, ID3D11Device *device)
{
	const int width = 250;
	const int height = 250;
	stickman_run_right = new MeridorGraphics::AnimatedSprite(sprite_batch.get(), { 0, 0, width, 250 }, -100, -100, 50, 50, 0.1f);
	stickman_run_right->AddTexture(L"Graphics\\stickman_right.png", device);
	for (int i = 0; i < 7; ++i)
	{
		stickman_run_right->AddFrame({ 0, height + height*i, width, height*2 + height*i });
	}
	
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
			stickman_run_right->SetX(-500 + i * 25+distance);
			stickman_run_right->SetY(0 + j * 25);
			stickman_run_right->Draw();
		}
	}
	stickman_run_right->Update(delta_time);
	sprite_batch->End();
	
}

