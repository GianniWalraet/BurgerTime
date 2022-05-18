#pragma once

class PlayerState : public State
{
public:
	PlayerState(PeterPepperComponent* pOwner) : m_pOwner{ pOwner } {}
	virtual ~PlayerState() override = default;
	virtual void HandleState() {};
protected:
	PeterPepperComponent* m_pOwner;
	float m_PlayerMovementSpeed = 100.f;
};

class WalkingLeftState : public PlayerState
{
public:
	WalkingLeftState(PeterPepperComponent* pOwner);
	void HandleState() override;
};

class WalkingRightState : public PlayerState
{
public:
	WalkingRightState(PeterPepperComponent* pOwner);
	void HandleState() override;
};