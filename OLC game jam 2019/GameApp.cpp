#include "GameApp.h"


GameApp::GameApp(HINSTANCE instance) : DirectXApplication(instance)
{
	common_states = std::make_unique<DirectX::CommonStates>(device);
	basic_effect = std::make_unique<DirectX::BasicEffect>(device);
	basic_effect->SetVertexColorEnabled(true);
	//game = new Game();

	void const* shaderByteCode;
	size_t byteCodeLength;

	basic_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	device->CreateInputLayout(DirectX::VertexPositionColor::InputElements,
		DirectX::VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		&input_layout);

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.f, float(window_width), float(window_height), 0.f, 0.f, 1.f);
	basic_effect->SetProjection(proj);

	sprite_batch = std::make_unique<DirectX::SpriteBatch>(device_context);
	primitive_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(device_context);
	sprite_font = std::make_unique<DirectX::SpriteFont>(device, L"Graphics\\myfile.spritefont", false);
	mouse = std::make_unique<DirectX::Mouse>();
	mouse->SetWindow(hwnd);
	mouse_tracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();
}

void GameApp::Update(float delta_time)
{
	if (reset)
	{
		reset = false;
		//delete game;
		//game = new Game();
	}
	mouse_tracker->Update(mouse->GetState());
	//game->Update(mouse_tracker, mouse);
}

void GameApp::Render(float delta_time)
{
	float f[4] = { 0.1,0.15,0.15,1.0f };
	device_context->ClearRenderTargetView(render_target_view, f);
	//DrawThings
	sprite_batch->Begin(DirectX::SpriteSortMode_FrontToBack);
	//Draw sprites
	sprite_batch->End();
	swap_chain->Present(0, 0);

}
