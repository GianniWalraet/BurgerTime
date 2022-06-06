#pragma once


class EnemySpawnerComponent final : public BaseComponent
{
public:
	EnemySpawnerComponent(const std::vector<glm::vec3>& spawnPositions, uint32_t maxEnemies) : m_SpawnPositions{ spawnPositions }, m_MaxEnemies{maxEnemies} {}
	virtual ~EnemySpawnerComponent() override = default;
	EnemySpawnerComponent(const EnemySpawnerComponent& other) = delete;
	EnemySpawnerComponent(EnemySpawnerComponent&& other) = delete;
	EnemySpawnerComponent& operator=(const EnemySpawnerComponent& other) = delete;
	EnemySpawnerComponent& operator=(EnemySpawnerComponent&& other) = delete;
protected:
	void Update() override;
private:
	std::vector<glm::vec3> m_SpawnPositions{};
	uint32_t m_MaxEnemies{};

	float m_SpawnDelay{ 3.f };
	float m_TimeSinceLastSpawn{};

	void SpawnEnemy();
};

