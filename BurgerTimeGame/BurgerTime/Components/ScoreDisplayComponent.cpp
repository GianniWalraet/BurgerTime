#include "pch.h"
#include "ScoreDisplayComponent.h"
#include "PeterPepperComponent.h"


ScoreDisplayComponent::ScoreDisplayComponent(const std::shared_ptr<PeterPepperComponent>& pPlayerC, const std::shared_ptr<TextComponent>& pTextC)
{
	m_pPlayer = pPlayerC;
	m_pText = pTextC;

	assert(!m_pPlayer.expired());
	assert(!m_pText.expired());

	m_pText.lock()->SetText("Score: " + std::to_string(m_pPlayer.lock()->GetScore()));
}

void ScoreDisplayComponent::OnNotify(Event event)
{
	switch (event)
	{
	case Event::ScoreChanged:
	case Event::PlayerDied:
		UpdateText();
		break;
	}
}

void ScoreDisplayComponent::UpdateText()
{
	if (m_pPlayer.expired() || m_pText.expired())
		return;

	m_pText.lock()->SetText("Score: " + std::to_string(m_pPlayer.lock()->GetScore()));
}