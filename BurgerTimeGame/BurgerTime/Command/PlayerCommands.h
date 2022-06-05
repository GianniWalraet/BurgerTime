#pragma once
#include "Components/PeterPepperComponent.h"
#include "Components/GridComponent.h"

class PlayerCommand : public Command
{
public:
	PlayerCommand(std::shared_ptr<GameObject> pActor) : Command(pActor) 
	{
		m_pGameObj = pActor;
		m_pPeterPepperComp = pActor->GetComponent<PeterPepperComponent>();
		m_pGrid = m_pGameObj.lock()->GetScene()->FindObjectWithTag("Level")->GetComponent<GridComponent>();
	}
	~PlayerCommand() override = default;
protected:
	std::weak_ptr<GameObject> m_pGameObj{};
	PeterPepperComponent* m_pPeterPepperComp;
	GridComponent* m_pGrid{};
};

class KillCommand final : public PlayerCommand
{
public:
	explicit KillCommand(std::shared_ptr<GameObject> pActor) : PlayerCommand(pActor) {}
	void Execute() override
	{
		if (!m_pGameObj.lock()->IsEnabled()) return;
		m_pPeterPepperComp->OnDie();
	}
};

class ScoreCommand final : public PlayerCommand
{
public:
	explicit ScoreCommand(std::shared_ptr<GameObject> pActor) : PlayerCommand(pActor) {}
	void Execute() override
	{
		if (!m_pGameObj.lock()->IsEnabled()) return;
		m_pPeterPepperComp->OnBurgerDropped();
	}
};

class MoveLeftCommand final : public PlayerCommand
{
public:
	explicit MoveLeftCommand(std::shared_ptr<GameObject> pActor) : PlayerCommand(pActor) { m_pController = pActor->GetComponent<ControllerComponent>(); }
	void Execute() override;
private:
	ControllerComponent* m_pController{};
};

class MoveRightCommand final : public PlayerCommand
{
public:
	explicit MoveRightCommand(std::shared_ptr<GameObject> pActor) : PlayerCommand(pActor) { m_pController = pActor->GetComponent<ControllerComponent>(); }
	void Execute() override;
private:
	ControllerComponent* m_pController{};
};

class MoveUpCommand final : public PlayerCommand
{
public:
	explicit MoveUpCommand(std::shared_ptr<GameObject> pActor) : PlayerCommand(pActor) { m_pController = pActor->GetComponent<ControllerComponent>(); }
	void Execute() override;
private:
	ControllerComponent* m_pController{};
};

class MoveDownCommand final : public PlayerCommand
{
public:
	explicit MoveDownCommand(std::shared_ptr<GameObject> pActor) : PlayerCommand(pActor) { m_pController = pActor->GetComponent<ControllerComponent>(); }
	void Execute() override;
private:
	ControllerComponent* m_pController{};
};
