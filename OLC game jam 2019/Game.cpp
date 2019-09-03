#include "Game.h"



Game::Game(DirectX::SpriteBatch* sprite_batch, ID3D11Device* device)
{
	stickman_animation_left_right = std::make_shared<StickmanAnimationLR>(sprite_batch, device);
	stickman_animation_zero = std::make_shared<StickmanAnimation0>(sprite_batch, device);
	player = std::make_unique<Player>(stickman_animation_left_right, stickman_animation_zero);
	for (int i = 0; i < 50; ++i)
		enemy.push_back(std::make_unique<Enemy>(stickman_animation_left_right, stickman_animation_zero));
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
	if(player)
		player->Draw();
	for (int i = 0; i < static_cast<int>(enemy.size()); ++i)
		enemy[i]->Draw();
	sprite_batch->End();
	
}

void Game::Update(const DirectX::Mouse::ButtonStateTracker * button_tracker, const DirectX::Mouse * mouse, const DirectX::Keyboard::KeyboardStateTracker * keyboard_tracker, const DirectX::Keyboard * keyboard, float delta_time)
{
	if (player)
	{
		auto keyboard_state = keyboard->GetState();
		player->Move({ static_cast<float>(keyboard_state.Right + keyboard_state.Left*-1),  static_cast<float>(keyboard_state.Up + keyboard_state.Down*-1) }, delta_time);
		player->Update(delta_time);
		for (int i = static_cast<int>(enemy.size()) - 1; i >= 0; --i)
		{
			DirectX::SimpleMath::Vector2 dir;
			if (player->GetX() - enemy[i]->GetX() > 0)
			{
				dir.x = 1;
			}
			else if (player->GetX() - enemy[i]->GetX() < -50)
			{
				dir.x = -1;
			}
			if (enemy[i]->GetY() - player->GetY() > 50)
			{
				dir.y = 1;
			}
			else if (enemy[i]->GetY() - player->GetY() < 0)
			{
				dir.y = -1;
			}
			enemy[i]->Move(dir, delta_time);
			enemy[i]->Update(delta_time);
			if (dir.x == 0 && dir.y == 0)
			{
				enemy.erase(enemy.begin() + i);
				hp -= 10;
				color = { 0.2f + static_cast<float>(100 - hp) / 100.0f , 0.8f - static_cast<float>(100 - hp) / 100.0f, 0.1f, 1.0f };
				if (hp < 0)
				{
					player.reset();
					break;
				}
			}
		}
	}
}

