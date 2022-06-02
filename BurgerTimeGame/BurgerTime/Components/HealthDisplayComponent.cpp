#include "pch.h"
#include "HealthDisplayComponent.h"
#include "PeterPepperComponent.h"

HealthDisplayComponent::HealthDisplayComponent(PeterPepperComponent* pPlayerC, TextComponent* pTextC)
{
	m_pPlayer = pPlayerC;
	m_pText = pTextC;

	assert(m_pPlayer != nullptr);
	assert(m_pText != nullptr);

	UpdateText();
}

void HealthDisplayComponent::Notify(Event event)
{
	switch (event)
	{
	case Event::PlayerDied:
		UpdateText();
		break;
	}
}

void HealthDisplayComponent::UpdateText()
{
	if (!m_pPlayer || !m_pText)
		return;

	m_pText->SetText("Lives: " + std::to_string(m_pPlayer->GetLives()));
}
