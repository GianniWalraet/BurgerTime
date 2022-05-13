#pragma once

class PlayerState abstract : public State
{
public:
	PlayerState(SpriteComponent* spriteComp) : m_pSpriteComp{ spriteComp } {}
	virtual ~PlayerState() override = default;
	virtual void HandleState() = 0;
protected:
	SpriteComponent* m_pSpriteComp;
};

class WalkingLeftState : public PlayerState
{
public:
	WalkingLeftState(SpriteComponent* spriteComp);
	void HandleState() override;
private:
};

class WalkingRightState : public PlayerState
{
public:
	WalkingRightState(SpriteComponent* spriteComp);
	void HandleState() override;
private:
};