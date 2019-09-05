#pragma once
#include "DirectXApplication.h"
#include "SimpleMath.h"
#include "PrimitiveBatch.h"
#include "VertexTypes.h"
#include "AnimationHeaders.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
	int hp = 100;
	bool alive = true;
	std::shared_ptr<StickmanAnimationLR> moving;
	std::shared_ptr<StickmanAnimationStay> staying;
	std::shared_ptr<StickmanAnimationKick> kicking;
	std::shared_ptr<StickmanAnimationFall> falling;
	std::unique_ptr<MeridorGraphics::Text>text;
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

