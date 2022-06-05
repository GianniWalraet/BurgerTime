#include "pch.h"
#include "MrHotDogComponent.h"

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
}

void MrHotDogComponent::Update()
{
	FindTarget();
	MoveToTarget();
}

void MrHotDogComponent::FindTarget()
{
	if (m_pPlayers.size() == 1) m_pTarget = m_pPlayers.front();


}
void MrHotDogComponent::MoveToTarget()
{
	if (m_pTarget.expired()) return;
	auto pos = m_pGameObject.lock()->GetTransform().GetPosition();
	auto playerPos = m_pTarget.lock()->GetTransform().GetPosition();

	int cellIdx = m_pGrid->PositionToIndex({ pos.x, pos.y });
	auto currentCell = m_pGrid->GetCell(cellIdx);

	
}