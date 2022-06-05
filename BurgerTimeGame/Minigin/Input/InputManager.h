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

	void SetActiveScene(const std::string& sceneName) { m_ActiveSceneID = sceneName; }
	void DisableInput() { m_InputDisabled = true; }
	void EnableInput() { m_InputDisabled = false; }

	// Controller
	bool IsPressed(UINT id, ControllerButton button) const;
	bool WentDownThisFrame(UINT id, ControllerButton button) const;
	bool WentUpThisFrame(UINT id, ControllerButton button) const;

	// Templated for command and actor who uses the command
	template <typename T>
	void AddCommand(const std::string& sceneID, UINT id, std::shared_ptr<GameObject> actor, ControllerButton button, InputState state = InputState::pressed)
	{
		//m_pConsoleCommands.emplace(std::pair<ControllerKey, std::unique_ptr<Command>>(ControllerKey{ { id, button}, state }, std::make_unique<T>(actor)));
		m_pConsoleCommands[sceneID].emplace(std::pair<ControllerKey, std::unique_ptr<T>>(ControllerKey{ { id, button}, state }, std::make_unique<T>(actor)));
	}
	void RemovedCommand(const std::string& sceneID, UINT id, ControllerButton button, InputState state = InputState::pressed)
	{
		auto it = m_pConsoleCommands[sceneID].find(ControllerKey{{id, button}, state});
		m_pConsoleCommands[sceneID].erase(it);
	}

	// Keyboard
	bool IsPressed(SDL_Keycode key) const;
	bool WentDownThisFrame(SDL_Keycode key) const;
	bool WentUpThisFrame(SDL_Keycode key) const;

	// Templated for command and actor who uses the command
	template <typename T>
	void AddCommand(const std::string& sceneID, std::shared_ptr<GameObject> actor, SDL_Keycode key, InputState state = InputState::pressed)
	{
		//m_pKeyboardCommands.emplace(std::pair<KeyboardKey, std::unique_ptr<Command>>(KeyboardKey{ key, state }, std::make_unique<T>(actor)));
		m_pKeyboardCommands[sceneID].emplace(std::pair<KeyboardKey, std::unique_ptr<T>>(KeyboardKey{ key, state }, std::make_unique<T>(actor)));
	}
	void RemovedCommand(const std::string& sceneID, SDL_Keycode key, InputState state = InputState::pressed)
	{
		auto it = m_pKeyboardCommands[sceneID].find(KeyboardKey{key,state});
		m_pKeyboardCommands[sceneID].erase(it);
	}

private:
	friend class Singleton<InputManager>;
	InputManager() = default;

	std::string m_ActiveSceneID{};
	bool m_InputDisabled{};

	std::unique_ptr<ControllerInput> m_pControllerInput;
	std::unique_ptr<SDLKeyboardInput> m_pKeyboardInput;

	std::unordered_map<std::string, std::map<ControllerKey, std::unique_ptr<Command>>> m_pConsoleCommands{};
	std::unordered_map<std::string, std::map<KeyboardKey, std::unique_ptr<Command>>> m_pKeyboardCommands{};
};
