#pragma once

class TextComponent;
class PeterPepperComponent;

class ScoreDisplayComponent final : public BaseComponent, public Observer
{
public:
	ScoreDisplayComponent(const std::shared_ptr<PeterPepperComponent>& pPlayerC, const std::shared_ptr<TextComponent>& pTextC);
	virtual ~ScoreDisplayComponent() = default;
	ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
	ScoreDisplayComponent(ScoreDisplayComponent&& other) = delete;
	ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
	ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) = delete;

	void OnNotify(Event event) override;
private:
	std::weak_ptr<PeterPepperComponent> m_pPlayer{};
	std::weak_ptr<TextComponent> m_pText{};

	void UpdateText();
};
