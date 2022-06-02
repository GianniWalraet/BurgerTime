#include "pch.h"
#include "PlayerCommands.h"

void MoveLeftCommand::Execute()
{
	m_pPeterPepperComp->SetState(State::moveHorizontal, Direction::left);

	auto& gridManager = GridManager::GetInstance();
	const auto& pos = m_pGameObj.lock()->GetTransform()->GetPosition();

	auto box = gridManager.GetBox({ pos.x, pos.y });
	auto boxLeft = gridManager.GetBox({ pos.x - box.boundingbox.w / 2.f, pos.y });

	if (!boxLeft.isSolid)
	{
		float speed = m_pController->GetMovementSpeed();
		m_pController->Move(-speed * Timer::GetInstance().GetElapsed(), 0.f);
	}
}
void MoveRightCommand::Execute()
{
	m_pPeterPepperComp->SetState(State::moveHorizontal, Direction::right);

	auto& gridManager = GridManager::GetInstance();
	const auto& pos = m_pGameObj.lock()->GetTransform()->GetPosition();

	auto box = gridManager.GetBox({ pos.x, pos.y });
	auto boxRight = gridManager.GetBox({ pos.x + box.boundingbox.w / 2.f, pos.y });

	if (!boxRight.isSolid)
	{
		float speed = m_pController->GetMovementSpeed();
		m_pController->Move(speed * Timer::GetInstance().GetElapsed(), 0.f);
	}
}
void MoveUpCommand::Execute()
{
	m_pPeterPepperComp->SetState(State::moveVertical, Direction::up);

	auto& gridManager = GridManager::GetInstance();
	const auto& pos = m_pGameObj.lock()->GetTransform()->GetPosition();

	auto box = gridManager.GetBox({ pos.x, pos.y });
	auto boxUp = gridManager.GetBox({ pos.x, pos.y - box.boundingbox.h / 4.f * 3.f });

	if (!boxUp.isSolid)
	{
		float speed = m_pController->GetMovementSpeed();
		m_pController->Move(0.f, -speed * Timer::GetInstance().GetElapsed());
	}
}
void MoveDownCommand::Execute()
{
	m_pPeterPepperComp->SetState(State::moveVertical, Direction::down);

	auto& gridManager = GridManager::GetInstance();
	const auto& pos = m_pGameObj.lock()->GetTransform()->GetPosition();

	auto box = gridManager.GetBox({ pos.x, pos.y });
	auto boxUp = gridManager.GetBox({ pos.x, pos.y + box.boundingbox.h / 4.f });

	if (!boxUp.isSolid)
	{
		float speed = m_pController->GetMovementSpeed();
		m_pController->Move(0.f, speed * Timer::GetInstance().GetElapsed());
	}
}