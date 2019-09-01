#include "GameApp.h"


GameApp::GameApp(HINSTANCE instance) : DirectXApplication(instance)
{
	common_states = std::make_unique<DirectX::CommonStates>(device);
	basic_effect = std::make_unique<DirectX::BasicEffect>(device);
	basic_effect->SetVertexColorEnabled(true);
	

	void const* shaderByteCode;
	size_t byteCodeLength;

	basic_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	device->CreateInputLayout(DirectX::VertexPositionColor::InputElements,
		DirectX::VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		&input_layout);

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.f, float(window_width), float(window_height), 0.f, 0.f, 1.f);
	basic_effect->SetProjection(proj);

	sprite_batch = std::make_shared<DirectX::SpriteBatch>(device_context);
	primitive_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(device_context);
	sprite_font = std::make_unique<DirectX::SpriteFont>(device, L"Graphics\\myfile.spritefont", false);
	mouse = std::make_unique<DirectX::Mouse>();
	mouse->SetWindow(hwnd);
	mouse_tracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();
	keyboard = std::make_unique<DirectX::Keyboard>();
	keyboard_tracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	game = std::make_unique<Game>(sprite_batch.get(), device);
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
	keyboard_tracker->Update(keyboard->GetState());
	game->Update(mouse_tracker.get(), mouse.get(), keyboard_tracker.get(), keyboard.get(), delta_time);
}

void GameApp::Render(float delta_time)
{
	Clear();
	game->DrawPrimitiveBatch(primitive_batch.get(), delta_time);
	game->DrawSpriteBatch(sprite_batch.get(), delta_time);
	swap_chain->Present(0, 0);
	

}

void GameApp::Clear()
{
	device_context->ClearRenderTargetView(render_target_view, DirectX::Colors::Red);
	device_context->ClearDepthStencilView(stencil_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	device_context->OMSetRenderTargets(1, &render_target_view, stencil_view);

	CD3D11_VIEWPORT viewPort(0.0f, 0.0f, static_cast<float>(window_width), static_cast<float>(window_height));
	device_context->RSSetViewports(1, &viewPort);

	device_context->OMSetBlendState(common_states->Opaque(), nullptr, 0xFFFFFFFF);
	device_context->OMSetDepthStencilState(common_states->DepthNone(), 0);
	device_context->RSSetState(common_states->CullNone());
	basic_effect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
	basic_effect->Apply(device_context);
	device_context->IASetInputLayout(input_layout);

}
