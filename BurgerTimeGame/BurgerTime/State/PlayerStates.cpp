#include "pch.h"
#include "PlayerStates.h"
#include "Components/PeterPepperComponent.h"
#include "Singletons/GridManager.h"

PlayerState::PlayerState(PeterPepperComponent* pOwner)
	: m_pOwner{ pOwner }
{
	m_pGameObj = m_pOwner->GetGameObject().lock();
	m_pController = pOwner->GetGameObject().lock()->GetComponent<ControllerComponent>();
}

void IdleState::OnStateSwitch()
{
	auto spriteComp = m_pOwner->GetGameObject().lock()->GetComponent<SpriteComponent>();

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
	auto spriteComp = m_pOwner->GetGameObject().lock()->GetComponent<SpriteComponent>();

	SDL_Rect source{};
	source.x = GRID_SIZE * 3;
	source.y = 0;
	source.w = GRID_SIZE * 3;
	source.h = GRID_SIZE;

	spriteComp->Reset(source, 1, 3, false);
}
void WalkingLeftState::HandleState()
{
	auto& gridManager = GridManager::GetInstance();
	const auto& pos = m_pGameObj.lock()->GetTransform()->GetPosition();

	auto box = gridManager.GetBox({ pos.x, pos.y });
	auto boxLeft = gridManager.GetBox({ pos.x - box.boundingbox.w / 2.f, pos.y });

	if (!boxLeft.isSolid)
	{
		float speed = m_pController->GetMovementSpeed();
		m_pController->Move(-speed * Timer::GetInstance().GetElapsed(), 0.f);
	}
}

void WalkingRightState::OnStateSwitch()
{
	auto spriteComp = m_pOwner->GetGameObject().lock()->GetComponent<SpriteComponent>();

	SDL_Rect source{};
	source.x = GRID_SIZE * 3;
	source.y = 0;
	source.w = GRID_SIZE * 3;
	source.h = GRID_SIZE;

	spriteComp->Reset(source, 1, 3, true);
}
void WalkingRightState::HandleState()
{
	auto& gridManager = GridManager::GetInstance();
	const auto& pos = m_pGameObj.lock()->GetTransform()->GetPosition();

	auto box = gridManager.GetBox({ pos.x, pos.y });
	auto boxRight = gridManager.GetBox({ pos.x + box.boundingbox.w / 2.f, pos.y });

	if (!boxRight.isSolid)
	{
		float speed = m_pController->GetMovementSpeed();
		m_pController->Move(speed * Timer::GetInstance().GetElapsed(), 0.f);
	}
}

void ClimbingUpState::OnStateSwitch()
{
	auto spriteComp = m_pOwner->GetGameObject().lock()->GetComponent<SpriteComponent>();

	SDL_Rect source{};
	source.x = GRID_SIZE * 6;
	source.y = 0;
	source.w = GRID_SIZE * 3;
	source.h = GRID_SIZE;

	spriteComp->Reset(source, 1, 3, false);
}
void ClimbingUpState::HandleState()
{
	auto& gridManager = GridManager::GetInstance();
	const auto& pos = m_pGameObj.lock()->GetTransform()->GetPosition();

	auto box = gridManager.GetBox({ pos.x, pos.y });
	auto boxUp = gridManager.GetBox({ pos.x, pos.y - box.boundingbox.h / 4.f * 3.f });

	if (!boxUp.isSolid)
	{
		float speed = m_pController->GetMovementSpeed();
		m_pController->Move(0.f, -speed * Timer::GetInstance().GetElapsed());
	}
}

void ClimbingDownState::OnStateSwitch()
{
	auto spriteComp = m_pOwner->GetGameObject().lock()->GetComponent<SpriteComponent>();

	SDL_Rect source{};
	source.x = 0;
	source.y = 0;
	source.w = GRID_SIZE * 3;
	source.h = GRID_SIZE;

	spriteComp->Reset(source, 1, 3, false);

}
void ClimbingDownState::HandleState()
{
	auto& gridManager = GridManager::GetInstance();
	const auto& pos = m_pGameObj.lock()->GetTransform()->GetPosition();

	auto box = gridManager.GetBox({ pos.x, pos.y });
	auto boxDown = gridManager.GetBox({ pos.x, pos.y + box.boundingbox.h / 4.f });

	if (!boxDown.isSolid)
	{
		float speed = m_pController->GetMovementSpeed();
		m_pController->Move(0.f, speed * Timer::GetInstance().GetElapsed());
	}
}