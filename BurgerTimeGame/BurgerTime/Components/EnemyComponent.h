#pragma once
#include "Components/EnemyComponent.h"
#include "PeterPepperComponent.h"

class EnemyComponent : public BaseComponent, public std::enable_shared_from_this<EnemyComponent>
{
public:
	EnemyComponent() = default;
	virtual ~EnemyComponent() override = default;
	EnemyComponent(const EnemyComponent& other) = delete;
	EnemyComponent(EnemyComponent&& other) = delete;
	EnemyComponent& operator=(const EnemyComponent& other) = delete;
	EnemyComponent& operator=(EnemyComponent&& other) = delete;
protected:
	void Initialize() override;
	void Update() override;
private:
	std::vector<std::weak_ptr<GameObject>> m_pPlayers{};
	std::weak_ptr<GameObject> m_pTarget{};

	std::weak_ptr<GridComponent> m_pGrid{};
	glm::vec2 m_MovementSpeed{ 100.f, 80.f };

	Direction m_Dir{ Direction::left };

	bool m_Climbing{ true }, m_Walking{ true };

	float m_PathChanged{};
	float m_ElapsedTime{};
	float m_CheckPathWaitTime{ 1.f };

	void FindTarget();
	void MoveToTarget();
	void HandlePathChoice();
};

