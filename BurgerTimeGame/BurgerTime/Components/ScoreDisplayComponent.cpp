#include "pch.h"
#include "ScoreDisplayComponent.h"
#include "PeterPepperComponent.h"


ScoreDisplayComponent::ScoreDisplayComponent(const std::shared_ptr<GameObject>& pOwner, PeterPepperComponent* pPlayerC, TextComponent* pTextC)
	: BaseComponent::BaseComponent(pOwner)
{
	m_pPlayer = pPlayerC;
	m_pText = pTextC;

	assert(m_pPlayer != nullptr);
	assert(m_pText != nullptr);

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