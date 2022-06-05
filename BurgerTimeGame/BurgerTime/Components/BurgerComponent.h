#pragma once

class PeterPepperComponent;

enum class BurgerType
{
	bunTop = 0,
	bunBottom = 1,
	cheese = 2,
	burger = 3,
	tomato = 4,
	salad = 5
};

class BurgerComponent final : public BaseComponent
{
public:
	BurgerComponent(const std::vector<int>& cellIndices);
	virtual ~BurgerComponent() = default;
	BurgerComponent(const BurgerComponent& other) = delete;
	BurgerComponent(BurgerComponent&& other) = delete;
	BurgerComponent& operator=(const BurgerComponent& other) = delete;
	BurgerComponent& operator=(BurgerComponent&& other) = delete;
protected:
	void Initialize() override;
	void Update() override;
private:
	std::vector<int> m_CellIndices{};
	std::vector<bool> m_IsSteppedOn{ false, false, false, false };

	PeterPepperComponent* m_pTriggerActor{};
	GridComponent* m_pGrid{};
	
	float m_DefaultFallVelocity{ -200.f };
	float m_FallVelocity{ -200.f };
	float m_FallAcceleration{ -300.f };

	bool m_IsDropping{};
	bool m_OnPlate{};
	bool m_NextPlatformTriggered{};

	void CheckCanDrop();
	bool CheckOnPlate(int cellIdx);

	void HandleBurgerDropping();
	void ApplyFallAcceleration();
};

