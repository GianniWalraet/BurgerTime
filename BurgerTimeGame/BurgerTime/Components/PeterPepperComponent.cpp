#include "pch.h"
#include "PeterPepperComponent.h"
#include <Observer/AchievementObserver.h>


PeterPepperComponent::~PeterPepperComponent()
{
	if (m_pState)
	{
		delete m_pState;
		m_pState = nullptr;
	}
}

void PeterPepperComponent::OnDie()
{
	if (m_Lives == 0) return;

	--m_Lives;
	m_Score -= m_ScoreLoss;
	ServiceLocator::GetSoundManager()->PlayEffect("Sounds/LoseLife.mp3", 50);

	if (m_Score < 0) m_Score = 0;

	NotifyAll(Event::PlayerDied);
}
void PeterPepperComponent::OnBurgerDropped()
{
	if (m_Lives == 0) return;

	m_Score += m_ScoreGain;

	ServiceLocator::GetSoundManager()->PlayEffect("Sounds/ScoreGain.mp3", 50, 0, false);
	NotifyAll(Event::BurgerDropped);

	if (m_Score >= 500 && !m_HasWon)
	{
		AchievementObserver::GetInstance().Notify(EAchievements::GameWin);
		m_HasWon = true;
	}
}
