#define WIN32_LEAN_AND_MEAN
#include "MiniginPCH.h"
#include "XBox360Controller.h"
#include <Windows.h>
#include <Xinput.h>

namespace dae
{
	class XBox360Controller::XBox360ControllerImpl
	{
	public:
		explicit XBox360ControllerImpl();
		void HandleInput();
		bool IsPressed(UINT id, ControllerButton button);
		bool WentDownThisFrame(UINT id, ControllerButton button);
		bool WentUpThisFrame(UINT id, ControllerButton button);
	private:
		XINPUT_STATE m_CurrentStates[XUSER_MAX_COUNT];
		XINPUT_STATE m_PreviousStates[XUSER_MAX_COUNT];

		unsigned int m_ButtonsPressed[XUSER_MAX_COUNT];
		unsigned int m_ButtonsReleasedThisFrame[XUSER_MAX_COUNT];
		unsigned int m_ButtonsPressedThisFrame[XUSER_MAX_COUNT];
	};
}


dae::XBox360Controller::XBox360Controller()
	: ControllerInput()
{
	m_pImpl = new XBox360ControllerImpl();
}
dae::XBox360Controller::~XBox360Controller()
{
	delete m_pImpl;
	m_pImpl = nullptr;
}
void dae::XBox360Controller::HandleInput()
{
	m_pImpl->HandleInput();
}
bool dae::XBox360Controller::IsPressed(UINT id, ControllerButton button)
{
	return m_pImpl->IsPressed(id, button);
}
bool dae::XBox360Controller::WentDownThisFrame(UINT id, ControllerButton button)
{
	return m_pImpl->WentDownThisFrame(id, button);
}
bool dae::XBox360Controller::WentUpThisFrame(UINT id, ControllerButton button)
{
	return m_pImpl->WentUpThisFrame(id, button);
}

dae::XBox360Controller::XBox360ControllerImpl::XBox360ControllerImpl()
	: m_CurrentStates{}
	, m_PreviousStates{}
	, m_ButtonsPressed{}
	, m_ButtonsReleasedThisFrame{}
	, m_ButtonsPressedThisFrame{}
{
	ZeroMemory(&m_CurrentStates, sizeof(XINPUT_STATE)* XUSER_MAX_COUNT);
	ZeroMemory(&m_PreviousStates, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
}
void dae::XBox360Controller::XBox360ControllerImpl::HandleInput()
{
	std::swap(m_PreviousStates, m_CurrentStates);
	ZeroMemory(&m_CurrentStates, sizeof(XINPUT_STATE) * XUSER_MAX_COUNT);
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		auto result = XInputGetState(i, &m_CurrentStates[i]);
		if (result == ERROR_SUCCESS)
		{
			auto buttonChanges{ m_CurrentStates[i].Gamepad.wButtons ^ m_PreviousStates[i].Gamepad.wButtons };
			m_ButtonsPressed[i] = m_CurrentStates[i].Gamepad.wButtons;
			m_ButtonsPressedThisFrame[i] = buttonChanges & m_CurrentStates[i].Gamepad.wButtons;
			m_ButtonsReleasedThisFrame[i] = buttonChanges & (~m_CurrentStates[i].Gamepad.wButtons);
		}
		else
		{
			m_ButtonsPressed[i] = 0;
			m_ButtonsPressedThisFrame[i] = 0;
			m_ButtonsReleasedThisFrame[i] = 0;
		}
	}
}
bool dae::XBox360Controller::XBox360ControllerImpl::IsPressed(UINT id, ControllerButton button)
{
	return (m_ButtonsPressed[id] & static_cast<unsigned int>(button));
}
bool dae::XBox360Controller::XBox360ControllerImpl::WentDownThisFrame(UINT id, ControllerButton button)
{
	return (m_ButtonsPressedThisFrame[id] & static_cast<unsigned int>(button));
}
bool dae::XBox360Controller::XBox360ControllerImpl::WentUpThisFrame(UINT id, ControllerButton button)
{
	return (m_ButtonsReleasedThisFrame[id] & static_cast<unsigned int>(button));
}