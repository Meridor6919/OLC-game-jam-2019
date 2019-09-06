#pragma once
#include "Object.h"
class BloodPool : public Object
{
	float life_time = 1.0f;
	float fading_time = 3.0f;
	DirectX::XMVECTORF32 color = { 0.5f,0.0f,0.0f,0.5f };
	DirectX::SimpleMath::Vector2 orientation_point;
	DirectX::SimpleMath::Vector4 hitbox;
public:
	BloodPool(DirectX::SimpleMath::Vector2 orientation_point) : Object(orientation_point)
	{
		this->orientation_point = orientation_point;
	}
	virtual bool Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor> *primitive_batch, DirectX::XMVECTORF32 background_color, float delta_time)
	{
		const float size = 30.0f;
		DirectX::SimpleMath::Vector3 v1(orientation_point.x, orientation_point.y, 0.0f);
		DirectX::SimpleMath::Vector3 v2(orientation_point.x - size, orientation_point.y+size, 0.f);
		DirectX::SimpleMath::Vector3 v3(orientation_point.x + size, orientation_point.y + size, 0.f);
		DirectX::SimpleMath::Vector3 v4(orientation_point.x + size, orientation_point.y - size, 0.f);
		DirectX::SimpleMath::Vector3 v5(orientation_point.x - size, orientation_point.y - size, 0.f);

		DirectX::VertexPositionColor vc1(v1, color);
		DirectX::VertexPositionColor vc2(v2, { 1.f, 1.f, 1.f, 0.f });
		DirectX::VertexPositionColor vc3(v3,  { 1.f, 1.f, 1.f, 0.f });
		DirectX::VertexPositionColor vc4(v4,  { 1.f, 1.f, 1.f, 0.f });
		DirectX::VertexPositionColor vc5(v5,  { 1.f, 1.f, 1.f, 0.f });

		primitive_batch->DrawTriangle(vc1, vc2, vc3);
		primitive_batch->DrawTriangle(vc1, vc3, vc4);
		primitive_batch->DrawTriangle(vc1, vc4, vc5);
		primitive_batch->DrawTriangle(vc1, vc5, vc2);

		if (fading)
		{
			fading_time -= delta_time;
			if (fading_time < 0)
			{
				return false;
			}
			else
			{
				DirectX::SimpleMath::Vector4 v_2(color);
				v_2.w -= delta_time / fading_time / 2;
				color = { v_2.x, v_2.y, v_2.z, v_2.w };
			}
		}
		else
		{
			life_time -= delta_time;
			if (life_time < 0)
			{
				fading = true;
			}
		}
		return true;
	}
};

