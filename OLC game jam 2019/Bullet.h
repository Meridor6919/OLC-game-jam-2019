#pragma once
#include "Object.h"
class Bullet :
	public Object
{
	float life_time = 3.0f;
	float fading_time = 1.0f;
	DirectX::XMVECTORF32 color = { 0.0f,0.0f,0.0f,1.0f };
	DirectX::SimpleMath::Vector2 orientation_point;
	DirectX::SimpleMath::Vector2 direction;
	DirectX::SimpleMath::Vector4 hitbox;
public:
	Bullet(DirectX::SimpleMath::Vector2 orientation_point, DirectX::SimpleMath::Vector2 direction) : Object(orientation_point)
	{
		this->orientation_point = orientation_point;
		this->direction = direction;
	}
	virtual bool Draw(DirectX::PrimitiveBatch<DirectX::VertexPositionColor> *primitive_batch, DirectX::XMVECTORF32 background_color, float delta_time)
	{
		const float size = 30.0f;
		DirectX::SimpleMath::Vector3 v1(orientation_point.x, orientation_point.y, 1.0f);
		DirectX::SimpleMath::Vector3 v2(orientation_point.x-30.0f*ceil(direction.x), orientation_point.y + 30.0f*ceil(direction.y), 0.0f);

		DirectX::VertexPositionColor vc1(v1, color);
		DirectX::VertexPositionColor vc2(v2, { 0.f, 0.f, 0.f, 0.f });

		primitive_batch->DrawLine(vc1, vc2);

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
				v_2.w -= delta_time / fading_time;
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
	void Update(float delta_time)
	{

		float modifier = sqrt(1 / (direction.x*direction.x + direction.y * direction.y));
		direction.x *= modifier;
		direction.y *= modifier;
		orientation_point.x += direction.x*300.0f*delta_time;
		orientation_point.y -= direction.y*delta_time*300.0f;
	}
};

