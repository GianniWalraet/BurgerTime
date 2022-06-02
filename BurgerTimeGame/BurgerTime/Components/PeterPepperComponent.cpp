#include "pch.h"
#include "PeterPepperComponent.h"
#include "Observer/AchievementObserver.h"


PeterPepperComponent::PeterPepperComponent()
	: m_Lives{3}
{
}

PeterPepperComponent::~PeterPepperComponent()
{
	if (m_pSetState)
	{
		delete m_pSetState;
		m_pSetState = nullptr;
	}

	delete m_pDefaultState;
	m_pDefaultState = nullptr;
}

void PeterPepperComponent::Initialize()
{
	m_pDefaultState = new IdleState(this);
	m_pCurrentState = m_pDefaultState;
}

void PeterPepperComponent::Update()
{
	m_pCurrentState = m_StateSet ? m_pSetState : m_pDefaultState;
	if (m_pCurrentState != m_pPreviousState)
	{
		m_pCurrentState->OnStateSwitch();
	}

	m_pCurrentState->HandleState();
	m_StateSet = false;
	m_pPreviousState = m_pCurrentState;
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
