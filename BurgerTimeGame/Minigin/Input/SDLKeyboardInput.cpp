#include "MiniginPCH.h"
#include "SDLKeyboardInput.h"


bool SDLKeyboardInput::HandleInput()
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
			if (std::find(m_Pressed.begin(), m_Pressed.end(), static_cast<uint32_t>(e.key.keysym.sym)) == m_Pressed.end())
			{
				m_PressedThisFrame.push_back(e.key.keysym.sym);
				m_Pressed.push_back(e.key.keysym.sym);
			}
		}
		if (e.type == SDL_KEYUP)
		{
			if (std::find(m_Pressed.begin(), m_Pressed.end(), static_cast<uint32_t>(e.key.keysym.sym)) != m_Pressed.end())
				m_Pressed.erase(std::remove(m_Pressed.begin(), m_Pressed.end(), static_cast<uint32_t>(e.key.keysym.sym)), m_Pressed.end());

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

bool SDLKeyboardInput::IsKeyPressed(SDL_Keycode key)
{
	return (std::find(m_Pressed.begin(), m_Pressed.end(), static_cast<uint32_t>(key)) != m_Pressed.end());
}
bool SDLKeyboardInput::WentUpThisFrame(SDL_Keycode key)
{
	return (std::find(m_ReleasedThisFrame.begin(), m_ReleasedThisFrame.end(), static_cast<uint32_t>(key)) != m_ReleasedThisFrame.end());
}
bool SDLKeyboardInput::WentDownThisFrame(SDL_Keycode key)
{
	return (std::find(m_PressedThisFrame.begin(), m_PressedThisFrame.end(), static_cast<uint32_t>(key)) != m_PressedThisFrame.end());;
}
