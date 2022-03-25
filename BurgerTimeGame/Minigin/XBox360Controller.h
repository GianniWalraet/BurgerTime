#pragma once
#include "ControllerInput.h"

namespace dae
{
	class XBox360Controller final : public ControllerInput
	{
	public:
		XBox360Controller();
		~XBox360Controller();
		XBox360Controller(const XBox360Controller& other) = delete;
		XBox360Controller(XBox360Controller&& other) = delete;
		XBox360Controller& operator=(const XBox360Controller& other) = delete;
		XBox360Controller& operator=(XBox360Controller&& other) = delete;

		void HandleInput() override;
		bool IsPressed(UINT id, ControllerButton button) override;
		bool WentDownThisFrame(UINT id, ControllerButton button) override;
		bool WentUpThisFrame(UINT id, ControllerButton button) override;
	private:
		class XBox360ControllerImpl;
		XBox360ControllerImpl* m_pImpl;
	};
}


