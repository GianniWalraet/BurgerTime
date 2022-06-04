#pragma once
#include "BaseComponent.h"

class Transform;

class ControllerComponent : public BaseComponent
{
public:
	ControllerComponent(const glm::vec2& movementSpeed);
	virtual ~ControllerComponent() = default;
	ControllerComponent(const ControllerComponent& other) = delete;
	ControllerComponent(ControllerComponent&& other) = delete;
	ControllerComponent& operator=(const ControllerComponent& other) = delete;
	ControllerComponent& operator=(ControllerComponent&& other) = delete;

	const glm::vec2& GetMovementSpeed() const { return m_MoveSpeed; }

	void Move(float dispX, float dispY);
private:
	glm::vec2 m_MoveSpeed{};
};

