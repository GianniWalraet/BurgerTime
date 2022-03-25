#include "MiniginPCH.h"
#include "SDLKeyboardInput.h"


bool dae::SDLKeyboardInput::HandleInput()
{
	m_PressedThisFrame.clear();
	m_ReleasedThisFrame.clear();

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		//ImGuiManager::GetInstance().HandleInput(e);

		if (e.type == SDL_QUIT)
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN)
		{
			m_PressedThisFrame.push_back(e.key.keysym.sym);
		}
		if (e.type == SDL_KEYUP)
		{
			m_ReleasedThisFrame.push_back(e.key.keysym.sym);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				break;
			case SDL_BUTTON_RIGHT:
				break;
			case SDL_BUTTON_MIDDLE:
				break;
			}
		}
	}

	return true;
}

bool dae::SDLKeyboardInput::IsKeyPressed(SDL_Keycode key)
{
	return (std::find(m_PressedThisFrame.begin(), m_PressedThisFrame.end(), static_cast<uint32_t>(key)) != m_PressedThisFrame.end());
}
bool dae::SDLKeyboardInput::KeyWentUpThisFrame(SDL_Keycode key)
{
	return (std::find(m_ReleasedThisFrame.begin(), m_ReleasedThisFrame.end(), static_cast<uint32_t>(key)) != m_ReleasedThisFrame.end());
}
