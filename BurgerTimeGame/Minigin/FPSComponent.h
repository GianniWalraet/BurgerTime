#pragma once
#include "BaseComponent.h"


	class TextureComponent;
	class TextComponent;

	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent() = default;
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		void Update() override;

		void SetTextComponent(TextComponent* pText) { m_pText = pText; }
	private:
		TextComponent* m_pText;
	};

