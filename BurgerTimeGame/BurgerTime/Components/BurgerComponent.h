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
	BurgerComponent(BurgerType type);
	virtual ~BurgerComponent() = default;
	BurgerComponent(const BurgerComponent& other) = delete;
	BurgerComponent(BurgerComponent&& other) = delete;
	BurgerComponent& operator=(const BurgerComponent& other) = delete;
	BurgerComponent& operator=(BurgerComponent&& other) = delete;

	void Update() override;
private:
	std::shared_ptr<Texture2D> m_pTexture{};
};

