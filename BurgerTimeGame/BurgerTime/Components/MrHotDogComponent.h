#pragma once
#include "EnemyComponent.h"

class MrHotDogComponent final : public EnemyComponent
{
public:
	MrHotDogComponent() = default;
	virtual ~MrHotDogComponent() override = default;
	MrHotDogComponent(const MrHotDogComponent& other) = delete;
	MrHotDogComponent(MrHotDogComponent&& other) = delete;
	MrHotDogComponent& operator=(const MrHotDogComponent& other) = delete;
	MrHotDogComponent& operator=(MrHotDogComponent&& other) = delete;
};

