#include "MiniginPCH.h"
#include "InputManager.h"

void InputManager::Initialize()
{
	m_pControllerInput = std::make_unique<XBox360Controller>();
	m_pKeyboardInput = std::make_unique<SDLKeyboardInput>();
}

bool InputManager::ProcessInput()
{
	m_pControllerInput->HandleInput();
	bool doContinue = m_pKeyboardInput->HandleInput();

	for (const auto& command : m_pConsoleCommands)
	{
		const auto& id = command.first.first.first;
		const auto& button = command.first.first.second;

		switch (command.first.second)
		{
		case InputState::pressed:
			if (IsPressed(id, button)) 
				command.second->Execute();
			break;
		case InputState::down:
			if (WentDownThisFrame(id, button)) 
				command.second->Execute();
			break;
		case InputState::up:
			if (WentUpThisFrame(id, button)) 
				command.second->Execute();
			break;
		}
		
	}


	for (const auto& command : m_pKeyboardCommands)
	{
		const auto& key = command.first.first;
		switch (command.first.second)
		{
		case InputState::pressed:
			if (IsPressed(key)) 
				command.second->Execute();
			break;
		case InputState::down:
			if (WentDownThisFrame(key)) 
				command.second->Execute();
			break;
		case InputState::up:
			if (WentUpThisFrame(key)) 
				command.second->Execute();
			break;
		}
		
	}


	return doContinue;
}

bool InputManager::IsPressed(UINT id, ControllerButton button) const
{
	return m_pControllerInput->IsPressed(id, button);
}
bool InputManager::WentDownThisFrame(UINT id, ControllerButton button) const
{
	return m_pControllerInput->WentDownThisFrame(id, button);
}
bool InputManager::WentUpThisFrame(UINT id, ControllerButton button) const
{
	return m_pControllerInput->WentUpThisFrame(id, button);
}

bool InputManager::IsPressed(SDL_Keycode key) const
{
	return m_pKeyboardInput->IsKeyPressed(key);
}
bool InputManager::WentDownThisFrame(SDL_Keycode key) const
{
	return m_pKeyboardInput->WentDownThisFrame(key);
}
bool InputManager::WentUpThisFrame(SDL_Keycode key) const
{
	return m_pKeyboardInput->WentUpThisFrame(key);
}

