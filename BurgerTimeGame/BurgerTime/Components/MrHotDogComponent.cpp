#include "pch.h"
#include "MrHotDogComponent.h"
#include "PeterPepperComponent.h"

void MrHotDogComponent::Initialize()
{
	if (auto players = m_pGameObject.lock()->GetScene()->FindObjectsWithTag("Player"); !players.empty())
	{
		m_pPlayers.assign(players.begin(), players.end());
	}

	if (auto lvl = m_pGameObject.lock()->GetScene()->FindObjectWithTag("Level"))
	{
		m_pGrid = lvl->GetComponent<GridComponent>();
	}

	auto trigger = m_pGameObject.lock()->GetComponent<Box2DComponent>();
	if (trigger)
	{
		trigger->SetOnOverlapCallback([&](std::shared_ptr<GameObject> pActor, std::shared_ptr<GameObject> pOther, CollisionType type)
			{
				if (pActor == m_pTarget.lock() && type == CollisionType::ENTER)
				{
					std::cout << "Attacking Player!\n";
					m_pTarget.lock()->GetComponent<PeterPepperComponent>()->OnDie();
				}
				else if (pActor == m_pTarget.lock() && type == CollisionType::EXIT)
				{
					std::cout << "Player running!\n";
				}
			});
	}
}
void MrHotDogComponent::Update()
{
	FindTarget();
	MoveToTarget();
}

void MrHotDogComponent::FindTarget()
{
	if (m_pPlayers.front().lock()->IsEnabled() && m_pPlayers.front().lock()->IsEnabled())
	{
		auto p1Pos = m_pPlayers.front().lock()->GetTransform().GetPosition();
		auto p2Pos = m_pPlayers.front().lock()->GetTransform().GetPosition();
	}
}
void MrHotDogComponent::MoveToTarget()
{
	if (m_pTarget.expired()) return;
	auto pos = m_pGameObject.lock()->GetTransform().GetPosition();
	auto playerPos = m_pTarget.lock()->GetTransform().GetPosition();

	int cellIdxEnemy = m_pGrid->PositionToIndex({ pos.x, pos.y });
	int cellIdxPlayer = m_pGrid->PositionToIndex({ playerPos.x, playerPos.y });
	auto currentCell = m_pGrid->GetCell(cellIdxEnemy);

	//auto cellLeft = m_pGrid->GetCell(cellIdxEnemy - 1);
	//auto cellRight = m_pGrid->GetCell(cellIdxEnemy + 1);
	//auto cellTop = m_pGrid->GetCell(cellIdxEnemy - m_pGrid->GetNrCols() - 1);
	//auto cellBottom = m_pGrid->GetCell(cellIdxEnemy + m_pGrid->GetNrCols() - 1);

	auto cellLeft = m_pGrid->GetCell(cellIdxEnemy - 1);
	auto cellRight = m_pGrid->GetCell(cellIdxEnemy + 1);
	auto cellTop = m_pGrid->GetCell(cellIdxEnemy - m_pGrid->GetNrCols());
	auto cellBottom = m_pGrid->GetCell(cellIdxEnemy + m_pGrid->GetNrCols());

	if (m_pGrid->IndexToCol(cellIdxEnemy) != m_pGrid->IndexToCol(cellIdxPlayer))
	{
		if (playerPos.x < pos.x && !cellLeft.isVoid)
		{
			pos.x -= m_MovementSpeed.x * Timer::GetInstance().GetElapsed();
		}
		else if (playerPos.x > pos.x && !cellRight.isVoid)
		{
			pos.x += m_MovementSpeed.x * Timer::GetInstance().GetElapsed();
		}
	}

	if (m_pGrid->IndexToRow(cellIdxEnemy) != m_pGrid->IndexToRow(cellIdxPlayer))
	{
		if (playerPos.y < pos.y && !cellTop.isVoid)
		{
			pos.y -= m_MovementSpeed.y * Timer::GetInstance().GetElapsed();
		}
		else if (playerPos.y > pos.y && !cellBottom.isVoid)
		{
			pos.y += m_MovementSpeed.y * Timer::GetInstance().GetElapsed();
		}
	}

	m_pGameObject.lock()->GetTransform().SetPosition(pos.x, pos.y, pos.z);
}

void MrHotDogComponent::CheckPlayerHit()
{
}