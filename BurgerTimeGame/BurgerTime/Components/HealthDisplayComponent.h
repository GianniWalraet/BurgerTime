#pragma once

class TextComponent;
class PeterPepperComponent;

class HealthDisplayComponent final : public BaseComponent, public Observer
{
public:
	HealthDisplayComponent(PeterPepperComponent* pPlayerC);
	virtual ~HealthDisplayComponent() = default;
	HealthDisplayComponent(const HealthDisplayComponent& other) = delete;
	HealthDisplayComponent(HealthDisplayComponent&& other) = delete;
	HealthDisplayComponent& operator=(const HealthDisplayComponent& other) = delete;
	HealthDisplayComponent& operator=(HealthDisplayComponent&& other) = delete;

	void Update() override;

	void OnNotify(Event event) override;
private:
	PeterPepperComponent* m_pPlayer{};

	std::shared_ptr<Texture2D> m_pTexture{};
};


