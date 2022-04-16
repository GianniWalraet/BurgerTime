#pragma once

class TextComponent;
class PeterPepperComponent;

class ScoreDisplayComponent final : public BaseComponent, public Observer
{
public:
	ScoreDisplayComponent(const std::shared_ptr<GameObject>& pOwner, PeterPepperComponent* pPlayerC, TextComponent* pTextC);
	virtual ~ScoreDisplayComponent() = default;
	ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
	ScoreDisplayComponent(ScoreDisplayComponent&& other) = delete;
	ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
	ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) = delete;

	void Notify(Event event) override;
private:
	PeterPepperComponent* m_pPlayer{};
	TextComponent* m_pText{};

	void UpdateText();
};
