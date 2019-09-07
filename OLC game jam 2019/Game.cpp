#include "Game.h"



Game::Game(DirectX::SpriteBatch* sprite_batch, ID3D11Device* device)
{
	moving = std::make_shared<StickmanAnimationLR>(sprite_batch, device);
	staying = std::make_shared<StickmanAnimationStay>(sprite_batch, device);
	kicking = std::make_shared<StickmanAnimationKick>(sprite_batch, device);
	falling = std::make_shared<StickmanAnimationFall>(sprite_batch, device);
	stanislaw_moving = std::make_shared<StanislawLR>(sprite_batch, device);

	player = std::make_unique<Player>(stanislaw_moving, stanislaw_moving);
	sprite_font = std::make_unique<DirectX::SpriteFont>(device, L"Graphics\\myfile.spritefont", true);
	DirectX::SimpleMath::Vector2 v2 = { 150, 300 };
	text = std::make_unique<MeridorGraphics::Text>(sprite_font.get(), sprite_batch, 64, v2);
	for (int i = 0; i < 100; ++i)
		enemy.push_back(std::make_unique<Enemy>(moving, kicking));
}

void Game::DrawPrimitiveBatch(DirectX::PrimitiveBatch<DirectX::VertexPositionColor> *primitive_batch, float delta_time)
{
	
	primitive_batch->Begin();
	DirectX::SimpleMath::Vector3 v1(0.f, 50.f, 1.0f);
	DirectX::SimpleMath::Vector3 v2(1200.f, 50.f, 1.f);
	DirectX::SimpleMath::Vector3 v3(0.f, 0.f, 1.f);
	DirectX::SimpleMath::Vector3 v4(1200.f, 0.f, 1.f);

	
	DirectX::VertexPositionColor vc1(v1, DirectX::Colors::Black);
	DirectX::VertexPositionColor vc2(v2, DirectX::Colors::Black);
	DirectX::VertexPositionColor vc3(v3, color);
	DirectX::VertexPositionColor vc4(v4, color);
	
	vc1.color = DirectX::SimpleMath::Vector4(color);
	vc2.color = DirectX::SimpleMath::Vector4(color);
	primitive_batch->DrawQuad(vc3, vc1, vc2, vc4);
	for (int i = 0; i < blood_pools.size(); ++i)
	{
		if (!blood_pools[i]->Draw(primitive_batch, DirectX::Colors::White, delta_time))
		{
			blood_pools.erase(blood_pools.begin() + i);
		}
	}
	for (int i = 0; i < bullets.size(); ++i)
	{
		if (!bullets[i]->Draw(primitive_batch, DirectX::Colors::White, delta_time))
		{
			bullets.erase(bullets.begin() + i);
		}
	}
	primitive_batch->End();
}

void Game::DrawSpriteBatch(DirectX::SpriteBatch * sprite_batch, float delta_time)
{
	static float timer = 1.0f;

	sprite_batch->Begin();
	if (alive)
	{
		player->Draw();
	}
	for (int i = 0; i < static_cast<int>(enemy.size()); ++i)
		enemy[i]->Draw();
	if (!alive)
	{
		timer -= delta_time;
		if (timer < 0.0f)
		{
			timer = 1 - timer;
		}
		text->SetFontSize(64.0f * (0.9f+timer/4));
		text->SetPosition({ 100 / (timer/4 + 0.45f), 300 });
		text->SetColor(DirectX::Colors::DarkRed);
		text->Draw(L"Press R to Reset");
		
	}
	sprite_batch->End();
}

void Game::Update(const DirectX::Mouse::ButtonStateTracker * button_tracker, const DirectX::Mouse * mouse, const DirectX::Keyboard::KeyboardStateTracker * keyboard_tracker, const DirectX::Keyboard * keyboard, float delta_time)
{
	for (int i = 0; i < bullets.size(); ++i)
	{
		bullets[i]->Update(delta_time);
	}
	if (alive)
	{
		if(enemy.size()< 1000)
			enemy.push_back(std::make_unique<Enemy>(moving, kicking));
		auto keyboard_state = keyboard->GetState();
		auto mouse_state = mouse->GetState();
		if (mouse_state.leftButton)
		{
			DirectX::SimpleMath::Vector2 v1;
			float sum = abs(player->GetX() - mouse_state.x + player->GetWidth()) + abs(player->GetY() + player->GetHeight() - mouse_state.y);
			v1.x = (player->GetX() - mouse_state.x + player->GetWidth()) / -sum;
			v1.y = (player->GetY() - mouse_state.y + player->GetHeight()) / sum;;
			DirectX::SimpleMath::Vector2 v2 = { player->GetX() + player->GetWidth()*roundf((v1.x+1)/2), player->GetY() + player->GetHeight()/2 };
			for (int j = 0; j < 4; ++j)
			{
				float spread_x = static_cast<float>(rand() % 100) / 500.0f - 1.0f / 10.0f;
				float spread_y = static_cast<float>(rand() % 100) / 500.0f - 1.0f / 10.0f;
				DirectX::SimpleMath::Vector2 v3 = { v1.x + spread_x, v1.y + spread_y };
				bullets.push_back(std::make_unique<Bullet>(v2, v3));
			}
		}

		DirectX::SimpleMath::Vector2 player_move = { static_cast<float>((keyboard_state.Right || keyboard_state.D) + (keyboard_state.Left || keyboard_state.A)*-1),  static_cast<float>((keyboard_state.Up || keyboard_state.W) + (keyboard_state.Down || keyboard_state.S)*-1) };
		float sum = abs(player_move.x) + abs(player_move.y);
		if (sum == 0)
		{
			sum = 1.0f;
		}
		player_move.x /= sum;
		player_move.y /= sum;
		player->Move(player_move, delta_time);
		player->Update(delta_time);
		for (int i = static_cast<int>(enemy.size()) - 1; i >= 0; --i)
		{
			DirectX::SimpleMath::Vector2 dir;

			float distance_x = abs(player->GetX() +player->GetWidth()/2 - enemy[i]->GetX() - enemy[i]->GetWidth()/2 );
			float distance_y = abs(player->GetY() + player->GetHeight() / 2 - enemy[i]->GetY() - enemy[i]->GetHeight()/2);
			if (distance_x*distance_x + distance_y * distance_y < player->GetWidth()/1.2f*enemy[i]->GetWidth()/1.2f)
			{
				dir.x = 0.0f;
				dir.y = 0.0f;
			}
			else
			{
				dir.x = distance_x/(distance_x+distance_y) * (((player->GetX() + player->GetWidth() / 2 - enemy[i]->GetX() - enemy[i]->GetWidth() / 2) > 0)*2 -1);
				dir.y = distance_y / (distance_x + distance_y) * (((player->GetY() + player->GetHeight() / 2 - enemy[i]->GetY() - enemy[i]->GetHeight() / 2) > 0) * -2 + 1);
			}
			enemy[i]->Move(dir, delta_time);
			enemy[i]->Update(delta_time);
			if (enemy[i]->Hit())
			{
				hp -= 10;
				DirectX::SimpleMath::Vector2 temp = { player->GetX() + player->GetWidth()/2, player->GetY() + player->GetHeight()/2 };
				blood_pools.push_back(std::make_unique<BloodPool>(temp));
				color = { 0.2f + static_cast<float>(100 - hp) / 100.0f , 0.8f - static_cast<float>(100 - hp) / 100.0f, 0.1f, 1.0f };
				if (hp < 0)
				{
					alive = false;
					break;
				}
			}
			for (int j = 0; j < static_cast<int>(bullets.size()); ++j)
			{
				DirectX::SimpleMath::Vector4 hitbox = { enemy[i]->GetX(), enemy[i]->GetY(), enemy[i]->GetX() + enemy[i]->GetWidth(), enemy[i]->GetY() + enemy[i]->GetHeight() };
				if (bullets[j]->Collision(hitbox))
				{
					DirectX::SimpleMath::Vector2 temp = { enemy[i]->GetX() + enemy[i]->GetWidth() / 2, enemy[i]->GetY() + enemy[i]->GetHeight() / 2 };
					blood_pools.push_back(std::make_unique<BloodPool>(temp));
					enemy.erase(enemy.begin() + i);
					bullets.erase(bullets.begin() + j);
					j--;
					hp += 1;
					if (hp > 100)
						hp = 100;
					color = { 0.2f + static_cast<float>(100 - hp) / 100.0f , 0.8f - static_cast<float>(100 - hp) / 100.0f, 0.1f, 1.0f };
					i -= 1;
					break;
				}
			}
		}
	}
}

