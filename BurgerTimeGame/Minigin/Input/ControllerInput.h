#pragma once


enum class ControllerButton
{
	GAMEPAD_DPAD_UP = 0x0001,
	GAMEPAD_DPAD_DOWN = 0x0002,
	GAMEPAD_DPAD_LEFT = 0x0004,
	GAMEPAD_DPAD_RIGHT = 0x0008,
	GAMEPAD_START = 0x0010,
	GAMEPAD_BACK = 0x0020,
	GAMEPAD_LEFT_THUMB = 0x0040,
	GAMEPAD_RIGHT_THUMB = 0x0080,
	GAMEPAD_LEFT_SHOULDER = 0x0100,
	GAMEPAD_RIGHT_SHOULDER = 0x0200,
	GAMEPAD_BUTTON_SOUTH = 0x1000,
	GAMEPAD_BUTTON_EAST = 0x2000,
	GAMEPAD_BUTTON_WEST = 0x4000,
	GAMEPAD_BUTTON_NORTH = 0x8000
};

class ControllerInput abstract
{
public:
	ControllerInput() = default;
	virtual ~ControllerInput() = default;
	virtual void HandleInput() = 0;
	virtual bool IsPressed(UINT id, ControllerButton button) = 0;
	virtual bool WentDownThisFrame(UINT id, ControllerButton button) = 0;
	virtual bool WentUpThisFrame(UINT id, ControllerButton button) = 0;
};


