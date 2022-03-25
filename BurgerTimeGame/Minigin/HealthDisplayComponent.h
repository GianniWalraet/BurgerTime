#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class TextComponent;
	class PeterPepperComponent;

	class HealthDisplayComponent final : public BaseComponent, public Observer
	{
	public:
		HealthDisplayComponent(PeterPepperComponent* pPlayer, TextComponent* pTxt);
		virtual ~HealthDisplayComponent() = default;
		HealthDisplayComponent(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent(HealthDisplayComponent&& other) = delete;
		HealthDisplayComponent& operator=(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent& operator=(HealthDisplayComponent&& other) = delete;
		
		void Notify(Event event) override;
	private:
		PeterPepperComponent* m_pPlayer{};
		TextComponent* m_pText{};

		void UpdateText();
	};
}


