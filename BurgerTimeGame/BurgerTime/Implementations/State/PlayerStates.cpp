#include "pch.h"
#include "PlayerStates.h"
#include "Components/PeterPepperComponent.h"

WalkingLeftState::WalkingLeftState(PeterPepperComponent* pOwner)
	: PlayerState(pOwner)
{
	auto spriteComp = pOwner->GetOwner().lock()->GetComponent<SpriteComponent>();

	SDL_Rect source{};
	source.x = GRID_SIZE * 3;
	source.y = 0;
	source.w = GRID_SIZE * 3;
	source.h = GRID_SIZE;
	
	spriteComp->SetSource(source);
	spriteComp->SetMirrored(false);
}
void WalkingLeftState::HandleState()
{
	auto go = m_pOwner->GetOwner().lock();
	auto pos = go->GetPosition();

	m_pOwner->GetOwner().lock()->SetPosition({ pos.x - m_PlayerMovementSpeed * Timer::GetInstance().GetElapsed(), pos.y, pos.z });
}
WalkingRightState::WalkingRightState(PeterPepperComponent* pOwner)
	: PlayerState(pOwner)
{
	auto spriteComp = pOwner->GetOwner().lock()->GetComponent<SpriteComponent>();

	SDL_Rect source{};
	source.x = GRID_SIZE * 3;
	source.y = 0;
	source.w = GRID_SIZE * 3;
	source.h = GRID_SIZE;

	spriteComp->SetSource(source);
	spriteComp->SetMirrored(true);
}
void WalkingRightState::HandleState()
{
	auto go = m_pOwner->GetOwner().lock();
	auto pos = go->GetPosition();

	m_pOwner->GetOwner().lock()->SetPosition({pos.x + m_PlayerMovementSpeed * Timer::GetInstance().GetElapsed(), pos.y, pos.z});
}
