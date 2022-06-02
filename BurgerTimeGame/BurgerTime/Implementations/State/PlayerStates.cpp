#include "pch.h"
#include "PlayerStates.h"
#include "Components/PeterPepperComponent.h"

PlayerState::PlayerState(PeterPepperComponent* pOwner)
	: m_pOwner{ pOwner }
{
	m_pController = pOwner->GetOwner().lock()->GetComponent<ControllerComponent>();
}

void IdleState::OnStateSwitch()
{
	auto spriteComp = m_pOwner->GetOwner().lock()->GetComponent<SpriteComponent>();

	SDL_Rect source{};
	source.x = GRID_SIZE * 4;
	source.y = 0;
	source.w = GRID_SIZE;
	source.h = GRID_SIZE;

	spriteComp->Reset(source, 1, 1, false);
}
void IdleState::HandleState()
{

}

void WalkingLeftState::OnStateSwitch()
{
	auto spriteComp = m_pOwner->GetOwner().lock()->GetComponent<SpriteComponent>();

	SDL_Rect source{};
	source.x = GRID_SIZE * 3;
	source.y = 0;
	source.w = GRID_SIZE * 3;
	source.h = GRID_SIZE;

	spriteComp->Reset(source, 1, 3, false);
}
void WalkingLeftState::HandleState()
{
	float speed = m_pController->GetMovementSpeed();
	m_pController->Move(-speed * Timer::GetInstance().GetElapsed(), 0.f);
}

void WalkingRightState::OnStateSwitch()
{
	auto spriteComp = m_pOwner->GetOwner().lock()->GetComponent<SpriteComponent>();

	SDL_Rect source{};
	source.x = GRID_SIZE * 3;
	source.y = 0;
	source.w = GRID_SIZE * 3;
	source.h = GRID_SIZE;

	spriteComp->Reset(source, 1, 3, true);
}
void WalkingRightState::HandleState()
{
	float speed = m_pController->GetMovementSpeed();
	m_pController->Move(speed * Timer::GetInstance().GetElapsed(), 0.f);
}

void ClimbingUpState::OnStateSwitch()
{
	auto spriteComp = m_pOwner->GetOwner().lock()->GetComponent<SpriteComponent>();

	SDL_Rect source{};
	source.x = GRID_SIZE * 6;
	source.y = 0;
	source.w = GRID_SIZE * 3;
	source.h = GRID_SIZE;

	spriteComp->Reset(source, 1, 3, false);
}
void ClimbingUpState::HandleState()
{
	float speed = m_pController->GetMovementSpeed();
	m_pController->Move(0.f, -speed * Timer::GetInstance().GetElapsed());
}

void ClimbingDownState::OnStateSwitch()
{
	auto spriteComp = m_pOwner->GetOwner().lock()->GetComponent<SpriteComponent>();

	SDL_Rect source{};
	source.x = 0;
	source.y = 0;
	source.w = GRID_SIZE * 3;
	source.h = GRID_SIZE;

	spriteComp->Reset(source, 1, 3, false);

}
void ClimbingDownState::HandleState()
{
	float speed = m_pController->GetMovementSpeed();
	m_pController->Move(0.f, speed * Timer::GetInstance().GetElapsed());
}