#include "pch.h"
#include "PeterPepperStates.h"

WalkingState::WalkingState(const std::shared_ptr<GameObject>& peterPepperObj, Direction /*walkDir*/)
	: PeterPepperState(peterPepperObj)
{
	m_pSpriteComp = peterPepperObj->GetComponent<SpriteComponent>();
}

ClimbingState::ClimbingState(const std::shared_ptr<GameObject>& peterPepperObj, Direction /*climbDir*/)
	: PeterPepperState(peterPepperObj)
{
	m_pSpriteComp = peterPepperObj->GetComponent<SpriteComponent>();
}
