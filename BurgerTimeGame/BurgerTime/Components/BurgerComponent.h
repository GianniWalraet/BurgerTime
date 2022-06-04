#pragma once

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

	void Update() override;
private:
	std::vector<int> m_CellIndices;
	std::vector<bool> m_IsSteppedOn{ false, false, false, false };

	float m_FallVelocity{};
	float m_FallAcceleration{ -98.1f };
};

