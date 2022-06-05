#include "pch.h"
#include "BurgerComponent.h"
#include "Components/PeterPepperComponent.h"
#include "Singletons/GameState.h"

BurgerComponent::BurgerComponent(const std::vector<int>& cellIndices)
	: m_CellIndices(cellIndices)
{

}

void BurgerComponent::Initialize()
{
	if (auto lvl = m_pGameObject.lock()->GetScene()->FindObjectWithTag("Level"))
	{
		m_pGrid = lvl->GetComponent<GridComponent>();
	}
}
void BurgerComponent::Update()
{
	if (m_OnPlate) return;

	if (m_NextPlatformTriggered)
	{
		for (int i = 0; i < m_CellIndices.size(); i++)
			m_pGrid->GetCell(m_CellIndices[i]).isTriggered = false;

		m_NextPlatformTriggered = false;
	}

	if (!m_IsDropping)
		CheckCanDrop();
	else
		HandleBurgerDropping();
}

void BurgerComponent::CheckCanDrop()
{
	for (size_t i = 0; i < m_CellIndices.size(); i++)
	{
		if (m_pGrid->GetCell(m_CellIndices[i]).isTriggered)
		{
			if (!m_IsSteppedOn[i])
			{
				m_IsSteppedOn[i] = true;
				if (m_pGrid->GetCell(m_CellIndices[i]).pActor.lock())
					ServiceLocator::GetSoundManager()->PlayEffect("Sounds/StepOnBurger.mp3", GameData::SoundeffectVolume, 0, false);
			}

			if (auto actor = m_pGrid->GetCell(m_CellIndices[i]).pActor.lock())
			{
				m_pTriggerActor = actor->GetComponent<PeterPepperComponent>();
			}
		}
	}

	if (std::all_of(m_IsSteppedOn.begin(), m_IsSteppedOn.end(), [](bool v) { return v; }))
	{
		m_IsDropping = true;
		if (m_pTriggerActor)
		{
			m_pTriggerActor->OnBurgerDropped();
			m_pTriggerActor = nullptr;
		}
	}
}
void BurgerComponent::HandleBurgerDropping()
{
	ApplyFallAcceleration();

	auto& transform = m_pGameObject.lock()->GetTransform();
	auto pos = transform.GetPosition();

	auto idx = m_pGrid->PositionToIndex({ pos.x, pos.y });
	if (std::find(m_CellIndices.begin(), m_CellIndices.end(), idx) != m_CellIndices.end())
		return;

	if (CheckOnPlate(idx)) return;

	auto& cell = m_pGrid->GetCell(idx);
	if (!cell.isBurgerPlatform) return;

	if (pos.y < cell.boundingbox.y)
	{
		for (int i = 0; i < m_IsSteppedOn.size(); ++i) m_IsSteppedOn[i] = false;
		m_CellIndices.clear();
		m_CellIndices = { idx, idx + 1, idx + 2, idx + 3 };
		m_FallVelocity = m_DefaultFallVelocity;
		m_IsDropping = false;

		for (int i = 0; i < m_CellIndices.size(); i++)
			m_pGrid->GetCell(m_CellIndices[i]).isTriggered = true;
		m_NextPlatformTriggered = true;

		ServiceLocator::GetSoundManager()->PlayEffect("Sounds/BurgerCollide.mp3", GameData::SoundeffectVolume, false);
	}
}

void BurgerComponent::ApplyFallAcceleration()
{
	auto elapsedTime = Timer::GetInstance().GetElapsed();
	auto& transform = m_pGameObject.lock()->GetTransform();

	auto pos = transform.GetPosition();
	m_FallVelocity += m_FallAcceleration * elapsedTime;
	pos.y -= m_FallVelocity * elapsedTime;
	transform.SetPosition(pos.x, pos.y, 0.f);
}
bool BurgerComponent::CheckOnPlate(int cellIdx)
{
	auto& cell = m_pGrid->GetCell(cellIdx);
	if (cell.isPlate || m_pGrid->GetCell(cellIdx + m_pGrid->GetNrCols()).hasBurger)
	{
		m_OnPlate = true;
		cell.hasBurger = true;
		GameState::GetInstance().OnSliceCompleted();
		return true;
	}

	return false;
}