#pragma once
#include "Base/Singleton.h"
#include "Command/Command.h"
#include "XBox360Controller.h"
#include "SDLKeyboardInput.h"

enum class InputState
{
	pressed,
	down,
	up
};


using ControllerKey = std::pair<std::pair<UINT, ControllerButton>, InputState>;
using KeyboardKey = std::pair<SDL_Keycode, InputState >;
class PeterPepperComponent;

class InputManager final : public Singleton<InputManager>
{
public:
	void Initialize();
	bool ProcessInput();

	// Controller
	bool IsPressed(UINT id, ControllerButton button) const;
	bool WentDownThisFrame(UINT id, ControllerButton button) const;
	bool WentUpThisFrame(UINT id, ControllerButton button) const;

	// Templated for command and actor who uses the command
	template <typename T, typename U>
	void AddCommand(UINT id, U* actor, ControllerButton button, InputState state = InputState::pressed)
	{
		m_pConsoleCommands[ControllerKey{ { id, button}, state }] = std::make_unique<T>(actor);
	}
	void RemovedCommand(UINT id, ControllerButton button, InputState state = InputState::pressed)
	{
		auto it = m_pConsoleCommands.find(ControllerKey{ {id, button}, state });
		m_pConsoleCommands.erase(it);
	}

	// Keyboard
	bool IsPressed(SDL_Keycode key) const;
	bool WentDownThisFrame(SDL_Keycode key) const;
	bool WentUpThisFrame(SDL_Keycode key) const;

	// Templated for command and actor who uses the command
	template <typename T, typename U>
	void AddCommand(U* actor, SDL_Keycode key, InputState state = InputState::pressed)
	{
		m_pKeyboardCommands[KeyboardKey{ key, state }] = std::make_unique<T>(actor);
	}
	void RemovedCommand(SDL_Keycode key, InputState state = InputState::pressed)
	{
		auto it = m_pKeyboardCommands.find(KeyboardKey{ key,state });
		m_pKeyboardCommands.erase(it);
	}

private:
	std::unique_ptr<XBox360Controller> m_pControllerInput;
	std::unique_ptr<SDLKeyboardInput> m_pKeyboardInput;

	std::map<ControllerKey, std::unique_ptr<Command>> m_pConsoleCommands{};
	std::map<KeyboardKey, std::unique_ptr<Command>> m_pKeyboardCommands{};
};
