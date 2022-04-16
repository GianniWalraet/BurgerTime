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
		if (WentDownThisFrame(command.first.first, command.first.second)) command.second->Execute();

	for (const auto& command : m_pKeyboardCommands)
		if (IsPressed(command.first)) command.second->Execute();

	return doContinue;
}

bool InputManager::IsPressed(UINT id, ControllerButton button) const
{
	return m_pControllerInput->IsPressed(id, button);
}
bool InputManager::WentDownThisFrame(UINT id, ControllerButton button)
{
	return m_pControllerInput->WentDownThisFrame(id, button);
}
bool InputManager::WentUpThisFrame(UINT id, ControllerButton button)
{
	return m_pControllerInput->WentUpThisFrame(id, button);
}

bool InputManager::IsPressed(SDL_Keycode key)
{
	return m_pKeyboardInput->IsKeyPressed(key);
}
bool InputManager::WentUpThisFrame(SDL_Keycode key)
{
	return m_pKeyboardInput->KeyWentUpThisFrame(key);
}

