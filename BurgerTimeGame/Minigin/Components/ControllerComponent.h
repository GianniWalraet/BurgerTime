#pragma once
#include "BaseComponent.h"

class Transform;

class ControllerComponent : public BaseComponent
{
public:
	ControllerComponent(float movementSpeed);
	virtual ~ControllerComponent() = default;
	ControllerComponent(const ControllerComponent& other) = delete;
	ControllerComponent(ControllerComponent&& other) = delete;
	ControllerComponent& operator=(const ControllerComponent& other) = delete;
	ControllerComponent& operator=(ControllerComponent&& other) = delete;

	const float GetMovementSpeed() const { return m_MoveSpeed; }

	void Move(float dispX, float dispY);
private:
	float m_MoveSpeed{};
};

