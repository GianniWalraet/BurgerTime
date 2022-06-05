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

	auto trigger = m_pGameObject.lock()->GetComponent<Box2DComponent>();
	if (trigger)
	{
		trigger->SetOnOverlapCallback([&](std::shared_ptr<GameObject> pActor, std::shared_ptr<GameObject> pOther, CollisionType type)
			{
				if (pActor == m_pTarget.lock() && type == CollisionType::ENTER)
				{
					m_pTarget.lock()->GetComponent<PeterPepperComponent>()->OnDie();
				}
			});
	}
}
void MrHotDogComponent::Update()
{
	FindTarget();
	HandlePathChoice();
	MoveToTarget();
}

void MrHotDogComponent::FindTarget()
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
void MrHotDogComponent::MoveToTarget()
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
void MrHotDogComponent::HandlePathChoice()
{
	if (m_pTarget.expired()) return;
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

	if (pos.x < 0.f) m_Dir = Direction::right;
	if (pos.x > ww) m_Dir = Direction::left;
	if (pos.y < 0.f) m_Dir = Direction::down;
	if (pos.y > wh) m_Dir = Direction::up;
	

	int cellIdxEnemy = m_pGrid->PositionToIndex({ pos.x, pos.y });
	auto currentCell = m_pGrid->GetCell(cellIdxEnemy);

	auto cellLeftOut = m_pGrid->GetCell({pos.x - (currentCell.boundingbox.w + 1.f), pos.y});
	auto cellRightOut = m_pGrid->GetCell({ pos.x + (currentCell.boundingbox.w + 1.f), pos.y });
	auto cellLeftIn= m_pGrid->GetCell({ pos.x - (currentCell.boundingbox.w - 1.f), pos.y });
	auto cellRightIn = m_pGrid->GetCell({ pos.x + (currentCell.boundingbox.w - 1.f), pos.y });
	auto cellTop = m_pGrid->GetCell(cellIdxEnemy - m_pGrid->GetNrCols());
	auto cellBottom = m_pGrid->GetCell(cellIdxEnemy + m_pGrid->GetNrCols());

	switch(m_Dir)
	{
	case Direction::left:
		if (!cellRightIn.isBurgerPlatform && !cellLeftIn.isBurgerPlatform)
		{
			std::cout << "walked left\n";
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
		}
		break;
	case Direction::right:
		if (!cellLeftIn.isBurgerPlatform && !cellRightIn.isBurgerPlatform)
		{
			std::cout << "walked right\n";
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
		}
		break;
	case Direction::up:
		if (cellLeftOut.isBurgerPlatform || cellRightOut.isBurgerPlatform)
		{
			std::cout << "ladder climbed\n";
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
		}
		break;
	case Direction::down:
			if (cellLeftOut.isBurgerPlatform || cellRightOut.isBurgerPlatform)
			{
				std::cout << "ladder descended\n";
				if (playerPos.x < pos.x && !cellLeftOut.isVoid)
				{
					if (pos.y > cellLeftOut.boundingbox.y + cellLeftOut.boundingbox.h / 4.f * 3.f)
					{
						m_Dir = Direction::left;
						m_PathChanged = true;
					}
				}
				if (playerPos.x > pos.x && !cellRightOut.isVoid)
				{
					if (pos.y > cellLeftOut.boundingbox.y + cellLeftOut.boundingbox.h / 4.f * 3.f)
					{
						m_Dir = Direction::right;
						m_PathChanged = true;
					}
				}
			}
		break;
	}
}
