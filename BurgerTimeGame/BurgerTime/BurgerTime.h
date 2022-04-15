#pragma once
#include "Minigin.h"

class BurgerTime : public Minigin
{
public:
	BurgerTime() = default;
	~BurgerTime() = default;
	BurgerTime(const BurgerTime& other) = delete;
	BurgerTime(BurgerTime&& other) noexcept = delete;
	BurgerTime& operator=(const BurgerTime& other) = delete;
	BurgerTime& operator=(BurgerTime&& other) noexcept = delete;

	void LoadGame() const override;
private:
	PeterPepperComponent* AddPlayer(GameObject* parent, uint32_t playerId, const glm::vec3& playerPos, const glm::vec3& healthDisplayPos, const glm::vec3& scoreDisplayPos) const;
};

