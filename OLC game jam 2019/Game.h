#pragma once
#include "DirectXApplication.h"
#include "SimpleMath.h"
#include "PrimitiveBatch.h"
#include "VertexTypes.h"
#include "AnimationHeaders.h"
#include "Player.h"
#include "Enemy.h"
#include "BloodPool.h"
#include "Bullet.h"
#include <float.h>

class Game
{
	long kills = 0;
	int hp = 100;
	bool alive = true;
	float last_spawn = 0.0f;
	std::shared_ptr<StickmanAnimationLR> moving;
	std::shared_ptr<StickmanAnimationStay> staying;
	std::shared_ptr<StickmanAnimationKick> kicking;
	std::shared_ptr<StickmanAnimationFall> falling;
	std::shared_ptr<StanislawLR> stanislaw_moving;
	std::shared_ptr<StanislawStay> stanislaw_staying;
	std::unique_ptr<MeridorGraphics::Text>text;
	std::vector<std::unique_ptr<BloodPool>> blood_pools;
	std::vector<std::unique_ptr<Bullet>> bullets;
	std::unique_ptr<DirectX::SpriteFont> sprite_font;
	std::unique_ptr<Player> player;
	std::vector<std::unique_ptr<Enemy>> enemy;
	DirectX::XMVECTORF32 color = { 0.2f , 0.8f, 0.1f, 1.0f };

public:
	Game(DirectX::SpriteBatch* sprite_batch, ID3D11Device *device);
	void DrawPrimitiveBatch(DirectX::PrimitiveBatch<DirectX::VertexPositionColor> *primitive_batch, float delta_time);
	void DrawSpriteBatch(DirectX::SpriteBatch *sprite_batch, float delta_time);
	void Update(const DirectX::Mouse::ButtonStateTracker * button_tracker, const DirectX::Mouse * mouse, const DirectX::Keyboard::KeyboardStateTracker * keyboard_tracker, const DirectX::Keyboard * keyboard, float delta_time);
	DirectX::XMVECTORF32 GetBackground() { return color; }
};

