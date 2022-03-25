#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class TextComponent;
	class PeterPepperComponent;

	class ScoreDisplayComponent final : public BaseComponent, public Observer
	{
	public:
		ScoreDisplayComponent(PeterPepperComponent* pPlayer, TextComponent* pTxt);
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
}