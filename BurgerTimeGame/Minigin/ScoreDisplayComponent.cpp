#include "MiniginPCH.h"
#include "ScoreDisplayComponent.h"
#include "PeterPepperComponent.h"
#include "TextComponent.h"

dae::ScoreDisplayComponent::ScoreDisplayComponent(PeterPepperComponent* pPlayer, TextComponent* pTxt)
{
	m_pPlayer = pPlayer;
	m_pText = pTxt;
	m_pText->SetText("Score: " + std::to_string(m_pPlayer->GetScore()));
}

void dae::ScoreDisplayComponent::Notify(Event event)
{
	switch (event)
	{
	case Event::BurgerDropped:
		UpdateText();
		break;
	}
}

void dae::ScoreDisplayComponent::UpdateText()
{
	if (!m_pPlayer || !m_pText)
		return;

	m_pText->SetText("Score: " + std::to_string(m_pPlayer->GetScore()));
}