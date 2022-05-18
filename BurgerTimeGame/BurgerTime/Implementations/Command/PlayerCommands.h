#pragma once
#include "Components/PeterPepperComponent.h"
#include "Implementations/State/PlayerStates.h"

class PlayerCommand : public Command
{
public:
	PlayerCommand(std::shared_ptr<GameObject> pActor) : Command(pActor) 
	{
		m_pPeterPepperComp = pActor->GetComponentFromChildren<PeterPepperComponent>();
	}
	~PlayerCommand() override = default;
protected:
	PeterPepperComponent* GetActor() const { return m_pPeterPepperComp; }
private:
	PeterPepperComponent* m_pPeterPepperComp;
};

class KillCommand final : public PlayerCommand
{
public:
	explicit KillCommand(std::shared_ptr<GameObject> pActor) : PlayerCommand(pActor) {}
	void Execute() override
	{
		GetActor()->OnDie();
	}
};

class ScoreCommand final : public PlayerCommand
{
public:
	explicit ScoreCommand(std::shared_ptr<GameObject> pActor) : PlayerCommand(pActor) {}
	void Execute() override
	{
		GetActor()->OnBurgerDropped();
	}
};

class MoveLeftCommand final : public PlayerCommand
{
public:
	explicit MoveLeftCommand(std::shared_ptr<GameObject> pActor) : PlayerCommand(pActor) {}
	void Execute() override
	{
		GetActor()->SetState<WalkingLeftState>();
	}
};

class MoveRightCommand final : public PlayerCommand
{
public:
	explicit MoveRightCommand(std::shared_ptr<GameObject> pActor) : PlayerCommand(pActor) {}
	void Execute() override
	{
		GetActor()->SetState<WalkingRightState>();
	}
};

class MoveUpCommand final : public PlayerCommand
{
public:
	explicit MoveUpCommand(std::shared_ptr<GameObject> pActor) : PlayerCommand(pActor) {}
	void Execute() override
	{
		//GetActor()->SetState(PlayerState::OnLadder, Direction::Up);
	}
};

class MoveDownCommand final : public PlayerCommand
{
public:
	explicit MoveDownCommand(std::shared_ptr<GameObject> pActor) : PlayerCommand(pActor) {}
	void Execute() override
	{
		//GetActor()->SetState(PlayerState::OnLadder, Direction::Down);
	}
};
