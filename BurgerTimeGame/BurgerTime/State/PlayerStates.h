#pragma once

class PlayerState : public State
{
public:
	PlayerState(PeterPepperComponent* pOwner);
	virtual ~PlayerState() override = default;

	virtual void OnStateSwitch() {};
	virtual void HandleState() {};
protected:
	std::weak_ptr<GameObject> m_pGameObj;
	PeterPepperComponent* m_pOwner{};
	ControllerComponent* m_pController{};
};

class IdleState final : public PlayerState
{
public:
	IdleState(PeterPepperComponent* pOwner) : PlayerState(pOwner) {}
	virtual ~IdleState() override = default;

	void OnStateSwitch() override;
	void HandleState() override;
};

class WalkingLeftState final : public PlayerState
{
public:
	WalkingLeftState(PeterPepperComponent* pOwner) : PlayerState(pOwner) {}
	virtual ~WalkingLeftState() override = default;

	void OnStateSwitch() override;
	void HandleState() override;
};

class WalkingRightState final : public PlayerState
{
public:
	WalkingRightState(PeterPepperComponent* pOwner) : PlayerState(pOwner) {}
	virtual ~WalkingRightState() override = default;

	void OnStateSwitch() override;
	void HandleState() override;
};

class ClimbingUpState final : public PlayerState
{
public:
	ClimbingUpState(PeterPepperComponent* pOwner) : PlayerState(pOwner) {}
	virtual ~ClimbingUpState() override = default;

	void OnStateSwitch() override;
	void HandleState() override;
};

class ClimbingDownState final : public PlayerState
{
public:
	ClimbingDownState(PeterPepperComponent* pOwner) : PlayerState(pOwner) {}
	virtual ~ClimbingDownState() override = default;

	void OnStateSwitch() override;
	void HandleState() override;
};