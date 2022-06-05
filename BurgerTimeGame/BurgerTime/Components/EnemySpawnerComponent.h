#pragma once


class EnemySpawnerComponent final : public BaseComponent
{
public:
	EnemySpawnerComponent() = default;
	virtual ~EnemySpawnerComponent() override = default;
	EnemySpawnerComponent(const EnemySpawnerComponent& other) = delete;
	EnemySpawnerComponent(EnemySpawnerComponent&& other) = delete;
	EnemySpawnerComponent& operator=(const EnemySpawnerComponent& other) = delete;
	EnemySpawnerComponent& operator=(EnemySpawnerComponent&& other) = delete;
protected:
	void Initialize() override;
	void Update() override;
private:

};

