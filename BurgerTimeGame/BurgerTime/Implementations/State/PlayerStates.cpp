#include "pch.h"
#include "PlayerStates.h"

#define GRID_SIZE 16
#define GAME_SCALE 3

WalkingLeftState::WalkingLeftState(SpriteComponent* spriteComp)
	: PlayerState(spriteComp)
{
	SDL_Rect source{};
	source.x = GRID_SIZE * 3;
	source.y = 0;
	source.w = GRID_SIZE * 3;
	source.h = GRID_SIZE;
	
	m_pSpriteComp->SetSource(source);
	m_pSpriteComp->SetMirrored(false);
}
void WalkingLeftState::HandleState()
{
}


WalkingRightState::WalkingRightState(SpriteComponent* spriteComp)
{
	SDL_Rect source{};
	source.x = GRID_SIZE * 3;
	source.y = 0;
	source.w = GRID_SIZE * 3;
	source.h = GRID_SIZE;

	m_pSpriteComp->SetSource(source);
	m_pSpriteComp->SetMirrored(false);
}
void WalkingRightState::HandleState()
{
}
