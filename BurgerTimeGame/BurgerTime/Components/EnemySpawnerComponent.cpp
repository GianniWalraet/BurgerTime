#include "pch.h"
#include "EnemySpawnerComponent.h"
#include "MrHotDogComponent.h"
#include "Base/Helpers.h"

void EnemySpawnerComponent::Update()
{
	m_TimeSinceLastSpawn += Timer::GetInstance().GetElapsed();

	if (m_TimeSinceLastSpawn > m_SpawnDelay)
	{
		SpawnEnemy();
		m_TimeSinceLastSpawn = 0.f;
	}
}

void EnemySpawnerComponent::SpawnEnemy()
{
	auto scene = m_pGameObject.lock()->GetScene();
	if (scene->FindNumObjectsWithTag("Enemy") >= m_MaxEnemies) return;

	auto pos = m_SpawnPositions[utils::RandomInt(0, static_cast<int>(m_SpawnPositions.size() - 1))];
	auto newEnemy = Helpers::AddMrHotDog(scene);
	newEnemy->GetTransform().SetPosition(pos);
}