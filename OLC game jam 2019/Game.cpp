#include "Game.h"



Game::Game(DirectX::SpriteBatch* sprite_batch, ID3D11Device* device)
{
	stickman_animation_left_right = std::make_shared<StickmanAnimationLR>(sprite_batch, device);
	stickman_animation_zero = std::make_shared<StickmanAnimation0>(sprite_batch, device);
	player = std::make_unique<Player>(stickman_animation_left_right, stickman_animation_zero);
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
	player->Draw();
	//stickman_animation_left_right->Update(delta_time);
	sprite_batch->End();
	
}

void Game::Update(const DirectX::Mouse::ButtonStateTracker * button_tracker, const DirectX::Mouse * mouse, const DirectX::Keyboard::KeyboardStateTracker * keyboard_tracker, const DirectX::Keyboard * keyboard, float delta_time)
{
	auto keyboard_state = keyboard->GetState();
	if (keyboard_state.Escape)
	{
		exit(0);
	}
	player->Move({ static_cast<float>(keyboard_state.Right + keyboard_state.Left*-1),  static_cast<float>(keyboard_state.Up + keyboard_state.Down*-1) }, delta_time);
	player->Update(delta_time);
	
}

