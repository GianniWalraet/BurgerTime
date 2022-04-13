#include "pch.h"
#include "HealthDisplayComponent.h"
#include "TextComponent.h"
#include "PeterPepperComponent.h"

HealthDisplayComponent::HealthDisplayComponent(PeterPepperComponent* pPlayer, TextComponent* pTxt)
{
	m_pPlayer = pPlayer;
	m_pText = pTxt;
	m_pText->SetText("Lives: " + std::to_string(m_pPlayer->GetLives()));
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
