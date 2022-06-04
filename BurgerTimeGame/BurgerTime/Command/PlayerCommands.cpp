#include "pch.h"
#include "PlayerCommands.h"

void MoveLeftCommand::Execute()
{
	m_pPeterPepperComp->SetState(State::moveHorizontal, Direction::left);

	auto& gridManager = GridManager::GetInstance();
	const auto& pos = m_pGameObj.lock()->GetTransform().GetPosition();

	auto box = gridManager.GetCell({ pos.x, pos.y });
	auto boxUpLeft = gridManager.GetCell({ pos.x - box.boundingbox.w , pos.y - box.boundingbox.h / 2.f });
	auto boxLeft = gridManager.GetCell({ pos.x - box.boundingbox.w, pos.y });

	if (!boxLeft.isVoid)
	{
		float speed = m_pController->GetMovementSpeed().x;
		m_pController->Move(-speed * Timer::GetInstance().GetElapsed(), 0.f);
	}
}
void MoveRightCommand::Execute()
{
	m_pPeterPepperComp->SetState(State::moveHorizontal, Direction::right);

	auto& gridManager = GridManager::GetInstance();
	const auto& pos = m_pGameObj.lock()->GetTransform().GetPosition();

	auto box = gridManager.GetCell({ pos.x, pos.y });
	auto boxUpRight = gridManager.GetCell({ pos.x + box.boundingbox.w , pos.y - box.boundingbox.h / 2.f });
	auto boxRight = gridManager.GetCell({ pos.x + box.boundingbox.w , pos.y });

	if (!boxRight.isVoid && !boxUpRight.isVoid)
	{
		float speed = m_pController->GetMovementSpeed().x;
		m_pController->Move(speed * Timer::GetInstance().GetElapsed(), 0.f);
	}
}
void MoveUpCommand::Execute()
{
	m_pPeterPepperComp->SetState(State::moveVertical, Direction::up);

	auto& gridManager = GridManager::GetInstance();
	const auto& pos = m_pGameObj.lock()->GetTransform().GetPosition();

	auto box = gridManager.GetCell({ pos.x, pos.y });
	auto boxUp = gridManager.GetCell({ pos.x, pos.y - box.boundingbox.h / 4.f * 3.f });

	if (!boxUp.isVoid)
	{
		float speed = m_pController->GetMovementSpeed().y;
		m_pController->Move(0.f, -speed * Timer::GetInstance().GetElapsed());
	}
}
void MoveDownCommand::Execute()
{
	m_pPeterPepperComp->SetState(State::moveVertical, Direction::down);

	auto& gridManager = GridManager::GetInstance();
	const auto& pos = m_pGameObj.lock()->GetTransform().GetPosition();

	auto box = gridManager.GetCell({ pos.x, pos.y });
	auto boxUp = gridManager.GetCell({ pos.x, pos.y + box.boundingbox.h / 4.f });

	if (!boxUp.isVoid)
	{
		float speed = m_pController->GetMovementSpeed().y;
		m_pController->Move(0.f, speed * Timer::GetInstance().GetElapsed());
	}
}