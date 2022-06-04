#include "MiniginPCH.h"
#include "CollisionManager.h"
#include "Base/Utils.h"

void CollisionManager::HandleCollision()
{
	for (auto& box : m_pCollisionBoxes)
	{
		for (auto& other : m_pCollisionBoxes)
		{
			if (box == other) continue;
			bool arePair = AreCollisionPair(box, other);

			if (utils::IsOverlapping(box->GetCollider(), other->GetCollider()))
			{
				if (!arePair)
				{
					box->OnOverlap(box->GetGameObject().lock(), other->GetGameObject().lock(), CollisionType::ENTER);
					other->OnOverlap(box->GetGameObject().lock(), other->GetGameObject().lock(), CollisionType::ENTER);
					m_pCollisionPairs.emplace_back(std::pair<Box2DComponent*, Box2DComponent*>(box, other));
				}
			}
			else if (arePair)
			{
				box->OnOverlap(box->GetGameObject().lock(), other->GetGameObject().lock(), CollisionType::EXIT);
				other->OnOverlap(box->GetGameObject().lock(), other->GetGameObject().lock(), CollisionType::EXIT);
				m_pCollisionPairs.erase(std::remove(m_pCollisionPairs.begin(), m_pCollisionPairs.end(), std::pair<Box2DComponent*, Box2DComponent*>(box,other)), m_pCollisionPairs.end());
			}
		}
	}
}

void CollisionManager::AddCollider(Box2DComponent* collider)
{
	m_pCollisionBoxes.emplace_back(collider);
}
void CollisionManager::RemoveCollider(Box2DComponent* collider)
{
	if (std::find(m_pCollisionBoxes.begin(), m_pCollisionBoxes.end(), collider) == m_pCollisionBoxes.end()) return;
	m_pCollisionBoxes.erase(std::remove(m_pCollisionBoxes.begin(), m_pCollisionBoxes.end(), collider), m_pCollisionBoxes.end());
}

bool CollisionManager::AreCollisionPair(Box2DComponent* b1, Box2DComponent* b2)
{
	return std::find(m_pCollisionPairs.begin(), m_pCollisionPairs.end(), std::pair<Box2DComponent*, Box2DComponent*>(b1, b2)) != m_pCollisionPairs.end();
}
