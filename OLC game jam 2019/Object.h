#pragma once
#include <string>
#include "DirectXApplication.h"
#include "SimpleMath.h"
#include "PrimitiveBatch.h"
#include "VertexTypes.h"
#include <DirectXColors.h>

class Object
{
protected:

	float life_time;
	float fading_time;
	bool fading = false;
	DirectX::XMVECTORF32 color;

	DirectX::SimpleMath::Vector4 hitbox;
	Object(DirectX::SimpleMath::Vector2 orientation_point) {}
	virtual bool Collision(DirectX::SimpleMath::Vector4 object) { return false; }
	virtual bool Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor> *primitive_batch, DirectX::XMVECTORF32 background_color, float delta_time) {return true;}
};
