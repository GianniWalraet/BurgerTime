#include "pch.h"
#include "PlayerStates.h"
#include "Components/PeterPepperComponent.h"

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
	auto go = m_pOwner->GetOwner().lock();
	auto pos = go->GetTransform()->GetPosition();

	m_pOwner->GetOwner().lock()->GetTransform()->SetPosition({ pos.x - m_PlayerMovementSpeed * Timer::GetInstance().GetElapsed(), pos.y, pos.z });
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
	auto go = m_pOwner->GetOwner().lock();
	auto pos = go->GetTransform()->GetPosition();

	m_pOwner->GetOwner().lock()->GetTransform()->SetPosition({pos.x + m_PlayerMovementSpeed * Timer::GetInstance().GetElapsed(), pos.y, pos.z});
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
	auto go = m_pOwner->GetOwner().lock();
	auto pos = go->GetTransform()->GetPosition();

	m_pOwner->GetOwner().lock()->GetTransform()->SetPosition({ pos.x , pos.y - m_PlayerMovementSpeed * Timer::GetInstance().GetElapsed(), pos.z });
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
	auto go = m_pOwner->GetOwner().lock();
	auto pos = go->GetTransform()->GetPosition();

	m_pOwner->GetOwner().lock()->GetTransform()->SetPosition({ pos.x , pos.y + m_PlayerMovementSpeed * Timer::GetInstance().GetElapsed(), pos.z });
}