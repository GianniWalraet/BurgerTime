#include "pch.h"
#include "PlayerCommands.h"

void MoveLeftCommand::Execute()
{
	if (m_pGameObj.expired()) return;
	if (!m_pGameObj.lock()->IsEnabled()) return;

	m_pPeterPepperComp.lock()->SetState(State::moveHorizontal, Direction::left);

	const auto& pos = m_pGameObj.lock()->GetTransform().GetPosition();

	auto box = m_pGrid.lock()->GetCell({ pos.x, pos.y });
	auto boxUpLeft = m_pGrid.lock()->GetCell({ pos.x - box.boundingbox.w , pos.y - box.boundingbox.h / 2.f });
	auto boxLeft = m_pGrid.lock()->GetCell({ pos.x - box.boundingbox.w, pos.y });

	if (!boxLeft.isVoid)
	{
		float speed = m_pController.lock()->GetMovementSpeed().x;
		m_pController.lock()->Move(-speed * Timer::GetInstance().GetElapsed(), 0.f);
	}
}
void MoveRightCommand::Execute()
{
	if (m_pGameObj.expired()) return;
	if (!m_pGameObj.lock()->IsEnabled()) return;

	m_pPeterPepperComp.lock()->SetState(State::moveHorizontal, Direction::right);

	const auto& pos = m_pGameObj.lock()->GetTransform().GetPosition();

	auto box = m_pGrid.lock()->GetCell({ pos.x, pos.y });
	auto boxUpRight = m_pGrid.lock()->GetCell({ pos.x + box.boundingbox.w , pos.y - box.boundingbox.h / 2.f });
	auto boxRight = m_pGrid.lock()->GetCell({ pos.x + box.boundingbox.w , pos.y });

	if (!boxRight.isVoid && !boxUpRight.isVoid)
	{
		float speed = m_pController.lock()->GetMovementSpeed().x;
		m_pController.lock()->Move(speed * Timer::GetInstance().GetElapsed(), 0.f);
	}
}
void MoveUpCommand::Execute()
{
	if (m_pGameObj.expired()) return;
	if (!m_pGameObj.lock()->IsEnabled()) return;

	m_pPeterPepperComp.lock()->SetState(State::moveVertical, Direction::up);

	const auto& pos = m_pGameObj.lock()->GetTransform().GetPosition();

	auto box = m_pGrid.lock()->GetCell({ pos.x, pos.y });
	auto boxUp = m_pGrid.lock()->GetCell({ pos.x, pos.y - box.boundingbox.h / 4.f * 3.f });

	if (!boxUp.isVoid)
	{
		float speed = m_pController.lock()->GetMovementSpeed().y;
		m_pController.lock()->Move(0.f, -speed * Timer::GetInstance().GetElapsed());
	}
}
void MoveDownCommand::Execute()
{
	if (m_pGameObj.expired()) return;
	if (!m_pGameObj.lock()->IsEnabled()) return;

	m_pPeterPepperComp.lock()->SetState(State::moveVertical, Direction::down);

	const auto& pos = m_pGameObj.lock()->GetTransform().GetPosition();

	auto box = m_pGrid.lock()->GetCell({ pos.x, pos.y });
	auto boxUp = m_pGrid.lock()->GetCell({ pos.x, pos.y + box.boundingbox.h / 4.f });

	if (!boxUp.isVoid)
	{
		float speed = m_pController.lock()->GetMovementSpeed().y;
		m_pController.lock()->Move(0.f, speed * Timer::GetInstance().GetElapsed());
	}
}