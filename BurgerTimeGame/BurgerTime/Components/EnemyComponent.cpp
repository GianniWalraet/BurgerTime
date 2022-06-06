#include "pch.h"
#include "EnemyComponent.h"

void EnemyComponent::Initialize()
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
				if (pActor != m_pTarget.lock()) return;
				auto ppComp = m_pTarget.lock()->GetComponent<PeterPepperComponent>();
				if (ppComp->IsStunned()) return;
				if (type == CollisionType::ENTER)
				{
					ppComp->AddCloseEnemy(shared_from_this());
				}
				else if (type == CollisionType::EXIT)
				{
					ppComp->RemoveCloseEnemy(shared_from_this());
				}

			});
	}
}
void EnemyComponent::Update()
{
	FindTarget();
	HandlePathChoice();
	MoveToTarget();
}

void EnemyComponent::FindTarget()
{
	auto pos = m_pGameObject.lock()->GetTransform().GetPosition();
	float nearDistance{ FLT_MAX };
	for (size_t i = 0; i < m_pPlayers.size(); i++)
	{
		if (m_pPlayers[i].expired() || !m_pPlayers[i].lock()->IsEnabled()) continue;
		auto playerPos = m_pPlayers[i].lock()->GetTransform().GetPosition();
		auto distance = utils::DistanceSquared(pos, playerPos);
		if (distance < nearDistance)
		{
			m_pTarget = m_pPlayers[i].lock();
			nearDistance = distance;
		}
	}
}
void EnemyComponent::MoveToTarget()
{
	auto pos = m_pGameObject.lock()->GetTransform().GetPosition();

	switch (m_Dir)
	{
	case Direction::left:
		pos.x -= m_MovementSpeed.x * Timer::GetInstance().GetElapsed();
		break;
	case Direction::right:
		pos.x += m_MovementSpeed.x * Timer::GetInstance().GetElapsed();
		break;
	case Direction::down:
		pos.y += m_MovementSpeed.y * Timer::GetInstance().GetElapsed();
		break;
	case Direction::up:
		pos.y -= m_MovementSpeed.y * Timer::GetInstance().GetElapsed();
		break;
	}

	m_pGameObject.lock()->GetTransform().SetPosition(pos.x, pos.y, pos.z);
}
void EnemyComponent::HandlePathChoice()
{
	if (m_pTarget.expired() || m_pGrid.expired()) return;

	const auto& pGrid = m_pGrid.lock();

	if (m_PathChanged)
	{
		m_ElapsedTime += Timer::GetInstance().GetElapsed();
		if (m_ElapsedTime > m_CheckPathWaitTime)
		{
			m_ElapsedTime = 0.f;
			m_PathChanged = false;
		}
		return;
	}

	auto pos = m_pGameObject.lock()->GetTransform().GetPosition();
	auto playerPos = m_pTarget.lock()->GetTransform().GetPosition();
	auto ww = Renderer::GetInstance().GetWindowWidth();
	auto wh = Renderer::GetInstance().GetWindowHeight();

	if (pos.x - GameData::SpriteCellSize * 2.f < 0.f) { m_Dir = Direction::right; return; }
	else if (pos.x + GameData::SpriteCellSize * 2.f > ww) { m_Dir = Direction::left; return; }
	else if (pos.y < 0.f) { m_Dir = Direction::down; return; }
	else if (pos.y > wh) { m_Dir = Direction::up; return; }


	int cellIdxEnemy = pGrid->PositionToIndex({ pos.x, pos.y });
	auto currentCell = pGrid->GetCell(cellIdxEnemy);

	auto cellLeftOut = pGrid->GetCell({ pos.x - (currentCell.boundingbox.w + 2.f), pos.y });
	auto cellRightOut = pGrid->GetCell({ pos.x + (currentCell.boundingbox.w + 2.f), pos.y });
	auto cellLeftIn = pGrid->GetCell({ pos.x - (currentCell.boundingbox.w - 2.f), pos.y });
	auto cellRightIn = pGrid->GetCell({ pos.x + (currentCell.boundingbox.w - 2.f), pos.y });
	auto cellTop = pGrid->GetCell(cellIdxEnemy - pGrid->GetNrCols());
	auto cellBottom = pGrid->GetCell(cellIdxEnemy + pGrid->GetNrCols());

	switch (m_Dir)
	{
	case Direction::left:
		if (!cellRightIn.isBurgerPlatform && !cellLeftIn.isBurgerPlatform)
		{
			if (playerPos.y > pos.y && !cellBottom.isVoid)
			{
				m_Dir = Direction::down;
				m_PathChanged = true;
			}
			else if (playerPos.y < pos.y && !cellTop.isVoid)
			{
				m_Dir = Direction::up;
				m_PathChanged = true;
			}
			else if (cellBottom.isVoid || cellTop.isVoid)
			{
				m_Dir = Direction::right;
			}
		}
		break;
	case Direction::right:
		if (!cellLeftIn.isBurgerPlatform && !cellRightIn.isBurgerPlatform)
		{
			if (playerPos.y > pos.y && !cellBottom.isVoid)
			{
				m_Dir = Direction::down;
				m_PathChanged = true;
			}
			else if (playerPos.y < pos.y && !cellTop.isVoid)
			{
				m_Dir = Direction::up;
				m_PathChanged = true;
			}
			else if (cellBottom.isVoid || cellTop.isVoid)
			{
				m_Dir = Direction::left;
			}
		}
		break;
	case Direction::up:
		if (cellLeftOut.isBurgerPlatform || cellRightOut.isBurgerPlatform)
		{
			if (playerPos.x < pos.x && !cellLeftOut.isVoid)
			{
				m_Dir = Direction::left;
				m_PathChanged = true;
			}
			else if (playerPos.x > pos.x && !cellRightOut.isVoid)
			{
				m_Dir = Direction::right;
				m_PathChanged = true;
			}
			else if (cellLeftOut.isVoid || cellRightOut.isVoid)
			{
				m_Dir = Direction::down;
			}
		}
		break;
	case Direction::down:
		if (cellLeftOut.isBurgerPlatform || cellRightOut.isBurgerPlatform)
		{
			if (playerPos.x < pos.x && !cellLeftOut.isVoid)
			{
				if (pos.y > cellLeftOut.boundingbox.y + cellLeftOut.boundingbox.h)
				{
					m_Dir = Direction::left;
					m_PathChanged = true;
				}
			}
			if (playerPos.x > pos.x && !cellRightOut.isVoid)
			{
				if (pos.y > cellLeftOut.boundingbox.y + cellLeftOut.boundingbox.h)
				{
					m_Dir = Direction::right;
					m_PathChanged = true;
				}
			}
			else if (cellLeftOut.isVoid && cellRightOut.isVoid)
			{
				m_Dir = Direction::up;
			}
		}
		break;
	}
}
