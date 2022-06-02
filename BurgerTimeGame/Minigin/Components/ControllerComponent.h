#pragma once
#include "BaseComponent.h"

class TransformComponent;

class ControllerComponent : public BaseComponent
{
public:
	ControllerComponent(const std::shared_ptr<GameObject>& pOwner, float movementSpeed) : BaseComponent::BaseComponent(pOwner), m_MoveSpeed{movementSpeed} {}
	virtual ~ControllerComponent() = default;
	ControllerComponent(const ControllerComponent& other) = delete;
	ControllerComponent(ControllerComponent&& other) = delete;
	ControllerComponent& operator=(const ControllerComponent& other) = delete;
	ControllerComponent& operator=(ControllerComponent&& other) = delete;

	void Move(float dispX, float dispY);
protected:
	void Initialize() override;
	void Update();
private:
	TransformComponent* m_pTransform;
	float m_MoveSpeed{};
};

