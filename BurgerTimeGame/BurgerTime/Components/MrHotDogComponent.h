#pragma once

class MrHotDogComponent final : public BaseComponent
{
public:
	MrHotDogComponent() = default;
	virtual ~MrHotDogComponent() override = default;
	MrHotDogComponent(const MrHotDogComponent& other) = delete;
	MrHotDogComponent(MrHotDogComponent&& other) = delete;
	MrHotDogComponent& operator=(const MrHotDogComponent& other) = delete;
	MrHotDogComponent& operator=(MrHotDogComponent&& other) = delete;
protected:
	void Initialize() override;
	void Update() override;
private:
	std::vector<std::weak_ptr<GameObject>> m_pPlayers{};
	std::weak_ptr<GameObject> m_pTarget{};

	GridComponent* m_pGrid{};
	glm::vec2 m_MovementSpeed{ 100.f, 100.f };

	void FindTarget();
	void MoveToTarget();
	void CheckPlayerHit();
};

