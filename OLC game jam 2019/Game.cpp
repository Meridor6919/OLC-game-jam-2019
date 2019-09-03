#include "Game.h"



Game::Game(DirectX::SpriteBatch* sprite_batch, ID3D11Device* device)
{
	moving = std::make_shared<StickmanAnimationLR>(sprite_batch, device);
	staying = std::make_shared<StickmanAnimation0>(sprite_batch, device);
	kicking = std::make_shared<StickmanAnimationKick>(sprite_batch, device);
	player = std::make_unique<Player>(moving, staying);
	sprite_font = std::make_unique<DirectX::SpriteFont>(device, L"Graphics\\myfile.spritefont", true);
	DirectX::SimpleMath::Vector2 v2 = { 150, 300 };
	text = std::make_unique<MeridorGraphics::Text>(sprite_font.get(), sprite_batch, 64, v2);
	for (int i = 0; i < 1; ++i)
		enemy.push_back(std::make_unique<Enemy>(moving, kicking));
}

void Game::DrawPrimitiveBatch(DirectX::PrimitiveBatch<DirectX::VertexPositionColor> *primitive_batch, float delta_time)
{
	
	primitive_batch->Begin();

	DirectX::SimpleMath::Vector3 v1(0.f, 50.f, 0.0f);
	DirectX::SimpleMath::Vector3 v2(1200.f, 50.f, 0.f);
	DirectX::SimpleMath::Vector3 v3(0.f, 0.f, 0.f);
	DirectX::SimpleMath::Vector3 v4(1200.f, 0.f, 0.f);

	
	DirectX::VertexPositionColor vc1(v1, DirectX::Colors::Black);
	DirectX::VertexPositionColor vc2(v2, DirectX::Colors::Black);
	DirectX::VertexPositionColor vc3(v3, color);
	DirectX::VertexPositionColor vc4(v4, color);

	primitive_batch->DrawLine(vc1, vc2);
	
	vc1.color = DirectX::SimpleMath::Vector4(color);;
	vc2.color = DirectX::SimpleMath::Vector4(color);;
	primitive_batch->DrawQuad(vc3, vc1, vc2, vc4);


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
	if (alive)
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
			if (enemy[i]->Hit())
			{
				hp -= 10;
				color = { 0.2f + static_cast<float>(100 - hp) / 100.0f , 0.8f - static_cast<float>(100 - hp) / 100.0f, 0.1f, 1.0f };
				if (hp < 0)
				{
					alive = false;
					break;
				}
			}
		}
	}
}

