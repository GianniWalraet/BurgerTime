#pragma once
#include "Base/Singleton.h"
#include "Components/Box2DComponent.h"


class CollisionManager : public Singleton<CollisionManager>
{
public:
	virtual ~CollisionManager() override = default;
	CollisionManager(const CollisionManager& other) = delete;
	CollisionManager(CollisionManager&& other) = delete;
	CollisionManager& operator=(const CollisionManager& other) = delete;
	CollisionManager& operator=(CollisionManager&& other) = delete;

	void HandleCollision();

	void AddCollider(Box2DComponent* collider);
	void RemoveCollider(Box2DComponent* collider);
private:
	friend class Singleton;
	CollisionManager() = default;

	std::vector<Box2DComponent*> m_pCollisionBoxes{};
	std::vector<std::pair<Box2DComponent*, Box2DComponent*>> m_pCollisionPairs{};

	bool AreCollisionPair(Box2DComponent* b1, Box2DComponent* b2);
};

