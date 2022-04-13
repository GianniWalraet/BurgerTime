#pragma once
#include "Command.h"
#include "PeterPepperComponent.h"

class PlayerCommand : public Command
{
public:
	PlayerCommand(PeterPepperComponent* pActor) : m_pActor{ pActor } {}
	~PlayerCommand() override = default;
protected:
	PeterPepperComponent* GetActor() const { return m_pActor; }
private:
	PeterPepperComponent* m_pActor;
};

class KillCommand final : public PlayerCommand
{
public:
	explicit KillCommand(PeterPepperComponent* actor) : PlayerCommand(actor) {}
	void Execute() override
	{
		GetActor()->OnDie();
	}
};

class ScoreCommand final : public PlayerCommand
{
public:
	explicit ScoreCommand(PeterPepperComponent* actor) : PlayerCommand(actor) {}
	void Execute() override
	{
		GetActor()->OnBurgerDropped();
	}
};

class MoveLeftCommand final : public PlayerCommand
{
public:
	explicit MoveLeftCommand(PeterPepperComponent* actor) : PlayerCommand(actor) {}
	void Execute() override
	{
		GetActor()->SetState(State::Walking, Direction::Left);
	}
};

class MoveRightCommand final : public PlayerCommand
{
public:
	explicit MoveRightCommand(PeterPepperComponent* actor) : PlayerCommand(actor) {}
	void Execute() override
	{
		GetActor()->SetState(State::Walking, Direction::Right);
	}
};

class MoveUpCommand final : public PlayerCommand
{
public:
	explicit MoveUpCommand(PeterPepperComponent* actor) : PlayerCommand(actor) {}
	void Execute() override
	{
		GetActor()->SetState(State::OnLadder, Direction::Up);
	}
};

class MoveDownCommand final : public PlayerCommand
{
public:
	explicit MoveDownCommand(PeterPepperComponent* actor) : PlayerCommand(actor) {}
	void Execute() override
	{
		GetActor()->SetState(State::OnLadder, Direction::Down);
	}
};
