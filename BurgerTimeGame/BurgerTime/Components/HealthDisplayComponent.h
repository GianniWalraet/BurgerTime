#pragma once

class TextComponent;
class PeterPepperComponent;

class HealthDisplayComponent final : public BaseComponent, public Observer
{
public:
	HealthDisplayComponent(PeterPepperComponent* pPlayerC, TextComponent* pTextC);
	virtual ~HealthDisplayComponent() = default;
	HealthDisplayComponent(const HealthDisplayComponent& other) = delete;
	HealthDisplayComponent(HealthDisplayComponent&& other) = delete;
	HealthDisplayComponent& operator=(const HealthDisplayComponent& other) = delete;
	HealthDisplayComponent& operator=(HealthDisplayComponent&& other) = delete;

	void Update() override;

	void Notify(Event event) override;
private:
	PeterPepperComponent* m_pPlayer{};
	TextComponent* m_pText{};

	std::shared_ptr<Texture2D> m_pTexture{};

	void UpdateText();
};


