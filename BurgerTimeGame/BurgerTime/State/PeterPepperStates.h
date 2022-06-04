#pragma once
#include "Components/PeterPepperComponent.h"

class PeterPepperState
{
public:
	PeterPepperState(const std::shared_ptr<GameObject>& peterPepperObj) : m_pGameObj{ peterPepperObj } {}
	virtual ~PeterPepperState() = default;

	virtual void HandleState() {}
protected:
	std::weak_ptr<GameObject>m_pGameObj{};
};

class WalkingState final : public PeterPepperState
{
public:
	WalkingState(const std::shared_ptr<GameObject>& peterPepperObj, Direction walkDir);
	virtual ~WalkingState() = default;
private:
	SpriteComponent* m_pSpriteComp{};
};

class ClimbingState final : public PeterPepperState
{
public:
	ClimbingState(const std::shared_ptr<GameObject>& peterPepperObj, Direction climbDir);
	virtual ~ClimbingState() = default;
private:
	SpriteComponent* m_pSpriteComp{};
};