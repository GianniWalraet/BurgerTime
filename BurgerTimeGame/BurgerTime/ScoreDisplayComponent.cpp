#include "pch.h"
#include "ScoreDisplayComponent.h"
#include "PeterPepperComponent.h"
#include "TextComponent.h"

ScoreDisplayComponent::ScoreDisplayComponent(PeterPepperComponent* pPlayer, TextComponent* pTxt)
{
	m_pPlayer = pPlayer;
	m_pText = pTxt;
	m_pText->SetText("Score: " + std::to_string(m_pPlayer->GetScore()));
}

void ScoreDisplayComponent::Notify(Event event)
{
	switch (event)
	{
	case Event::BurgerDropped:
		UpdateText();
		break;
	}
}

void ScoreDisplayComponent::UpdateText()
{
	if (!m_pPlayer || !m_pText)
		return;

	m_pText->SetText("Score: " + std::to_string(m_pPlayer->GetScore()));
}