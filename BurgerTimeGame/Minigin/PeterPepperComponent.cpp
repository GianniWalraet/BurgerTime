#include "pch.h"
#include "PeterPepperComponent.h"
#include "InputManager.h"
#include "Observer.h"
#include "AchievementObserver.h"
#include "GameObject.h"
#include "Timer.h"

PeterPepperComponent::PeterPepperComponent()
	: m_Lives{ 3 }
{

}
PeterPepperComponent::~PeterPepperComponent()
{
}

void PeterPepperComponent::OnDie()
{
	if (m_Lives == 0) return;

	--m_Lives;
	m_Score -= m_ScoreLoss;
	if (m_Score < 0) m_Score = 0;
	NotifyAll(Event::PlayerDied);
}
void PeterPepperComponent::OnBurgerDropped()
{
	if (m_Lives == 0) return;

	m_Score += m_ScoreGain;
	NotifyAll(Event::BurgerDropped);

	if (m_Score >= 500 && !m_HasWon)
	{
		AchievementObserver::GetInstance().Notify(EAchievements::GameWin);
		m_HasWon = true;
	}
}

void PeterPepperComponent::SetState(State state, Direction dir)
{
	switch (state)
	{
	case State::Walking:
		Move(dir);
		break;
	case State::OnLadder:
		Climb(dir);
		break;
	case State::ThrowSalt:
		break;
	case State::Dead:
		break;
	}
}

void PeterPepperComponent::Move(Direction dir)
{
	const float movement = (dir == Direction::Left) ? -1.f : 1.f;
	const auto& pos = m_pOwner.lock()->GetPosition();

	m_pOwner.lock()->SetPosition({ pos.x + (m_MovementSpeed * movement) * Timer::GetInstance().GetElapsed(), pos.y, pos.z });
}
void PeterPepperComponent::Climb(Direction dir)
{
	const float movement = (dir == Direction::Up) ? -1.f : 1.f;
	const auto& pos = m_pOwner.lock()->GetPosition();

	m_pOwner.lock()->SetPosition({ pos.x, pos.y + (m_MovementSpeed * movement) * Timer::GetInstance().GetElapsed(), pos.z });
}