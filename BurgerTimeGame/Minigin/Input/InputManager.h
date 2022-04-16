#pragma once
#include "Base/Singleton.h"
#include "Command/Command.h"
#include "XBox360Controller.h"
#include "SDLKeyboardInput.h"
#include <map>


using ControllerKey = std::pair<UINT, ControllerButton>;
class PeterPepperComponent;

class InputManager final : public Singleton<InputManager>
{
public:
	void Initialize();
	bool ProcessInput();

	// Controller
	bool IsPressed(UINT id, ControllerButton button) const;
	bool WentDownThisFrame(UINT id, ControllerButton button);
	bool WentUpThisFrame(UINT id, ControllerButton button);

	// Templated for command and actor who uses the command
	template <typename T, typename U>
	void AddCommand(UINT id, U* actor, ControllerButton button)
	{
		m_pConsoleCommands[ControllerKey{ id, button }] = std::make_unique<T>(actor);
	}
	void RemovedCommand(UINT id, ControllerButton button)
	{
		auto it = m_pConsoleCommands.find(ControllerKey{ id, button });
		m_pConsoleCommands.erase(it);
	}

	// Keyboard
	bool IsPressed(SDL_Keycode key);
	bool WentUpThisFrame(SDL_Keycode key);

	// Templated for command and actor who uses the command
	template <typename T, typename U>
	void AddCommand(U* actor, SDL_Keycode key)
	{
		m_pKeyboardCommands[key] = std::make_unique<T>(actor);
	}
	void RemovedCommand(SDL_Keycode key)
	{
		auto it = m_pKeyboardCommands.find(key);
		m_pKeyboardCommands.erase(it);
	}

private:
	std::unique_ptr<XBox360Controller> m_pControllerInput;
	std::unique_ptr<SDLKeyboardInput> m_pKeyboardInput;

	std::map<ControllerKey, std::unique_ptr<Command>> m_pConsoleCommands{};
	std::map<SDL_Keycode, std::unique_ptr<Command>> m_pKeyboardCommands{};
};