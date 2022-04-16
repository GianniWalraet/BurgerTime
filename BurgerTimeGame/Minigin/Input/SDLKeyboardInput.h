#pragma once


	class SDLKeyboardInput
	{
	public:
		bool HandleInput();
		bool IsKeyPressed(SDL_Keycode key);
		bool KeyWentUpThisFrame(SDL_Keycode key);
	private:
		std::vector<uint32_t> m_Pressed{};
		std::vector<uint32_t> m_ReleasedThisFrame{};
	};


