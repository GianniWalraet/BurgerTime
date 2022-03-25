#pragma once

namespace dae
{
	class SDLKeyboardInput
	{
	public:
		bool HandleInput();
		bool IsKeyPressed(SDL_Keycode key);
		bool KeyWentUpThisFrame(SDL_Keycode key);
	private:
		std::vector<uint32_t> m_PressedThisFrame{};
		std::vector<uint32_t> m_ReleasedThisFrame{};
	};
}

