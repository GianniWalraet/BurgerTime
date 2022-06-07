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
	std::weak_ptr<PeterPepperComponent> m_pPeterPepperComp;
	std::weak_ptr<GridComponent> m_pGrid{};
};


class MoveLeftCommand final : public PlayerCommand
{
public:
	explicit MoveLeftCommand(std::shared_ptr<GameObject> pActor) : PlayerCommand(pActor) { m_pController = pActor->GetComponent<ControllerComponent>(); }
	void Execute() override;
private:
	std::weak_ptr<ControllerComponent> m_pController{};
};

class MoveRightCommand final : public PlayerCommand
{
public:
	explicit MoveRightCommand(std::shared_ptr<GameObject> pActor) : PlayerCommand(pActor) { m_pController = pActor->GetComponent<ControllerComponent>(); }
	void Execute() override;
private:
	std::weak_ptr<ControllerComponent> m_pController{};
};

class MoveUpCommand final : public PlayerCommand
{
public:
	explicit MoveUpCommand(std::shared_ptr<GameObject> pActor) : PlayerCommand(pActor) { m_pController = pActor->GetComponent<ControllerComponent>(); }
	void Execute() override;
private:
	std::weak_ptr<ControllerComponent> m_pController{};
};

class MoveDownCommand final : public PlayerCommand
{
public:
	explicit MoveDownCommand(std::shared_ptr<GameObject> pActor) : PlayerCommand(pActor) { m_pController = pActor->GetComponent<ControllerComponent>(); }
	void Execute() override;
private:
	std::weak_ptr<ControllerComponent> m_pController{};
};
