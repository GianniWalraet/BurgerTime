#include "MiniginPCH.h"
#include "PeterPepperComponent.h"
#include "InputManager.h"
#include "Observer.h"
#include "AchievementObserver.h"

dae::PeterPepperComponent::PeterPepperComponent()
	: m_Lives{ 3 }
{

}
dae::PeterPepperComponent::~PeterPepperComponent()
{
}

void dae::PeterPepperComponent::OnDie()
{
	if (m_Lives == 0) return;

	--m_Lives;
	m_Score -= m_ScoreLoss;
	if (m_Score < 0) m_Score = 0;
	NotifyAll(Event::PlayerDied);
}
void dae::PeterPepperComponent::OnBurgerDropped()
{
	if (m_Lives == 0) return;

	m_Score += m_ScoreGain;
	NotifyAll(Event::BurgerDropped);

	if (m_Score >= 500) AchievementObserver::GetInstance().Notify(EAchievements::GameWin);
}
