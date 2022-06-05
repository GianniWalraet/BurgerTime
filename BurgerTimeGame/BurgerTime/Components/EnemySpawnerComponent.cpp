#include "pch.h"
#include "EnemySpawnerComponent.h"
#include "MrHotDogComponent.h"
#include "Base/Helpers.h"


void EnemySpawnerComponent::Initialize()
{

}
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
	if (scene->FindNumObjectsWithTag("Enemy") > m_MaxEnemies) return;

	m_SpawnPointIdx = (m_SpawnPointIdx + 1) % m_SpawnPositions.size();

	auto pos = m_SpawnPositions[m_SpawnPointIdx];
	auto newEnemy = Helpers::AddMrHotDog(scene);
	newEnemy->GetTransform().SetPosition(pos);
}