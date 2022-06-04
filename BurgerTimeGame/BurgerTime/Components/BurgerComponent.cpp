#include "pch.h"
#include "BurgerComponent.h"
#include "Components/PeterPepperComponent.h"

BurgerComponent::BurgerComponent(const std::vector<int>& cellIndices)
	: m_CellIndices(cellIndices)
	, m_BurgerPieces{int(cellIndices.size())}
{

}

void BurgerComponent::Update()
{
	if (m_OnPlate) return;

	auto& gridManager = GridManager::GetInstance();
	if (m_NextPlatformTriggered)
	{
		for (int i = 0; i < m_CellIndices.size(); i++)
			gridManager.GetCell(m_CellIndices[i]).isTriggered = false;

		m_NextPlatformTriggered = false;
	}

	if (!m_IsDropping)
		CheckCanDrop();
	else
		HandleBurgerDropping();
}

void BurgerComponent::CheckCanDrop()
{
	auto& gridManager = GridManager::GetInstance();

	for (size_t i = 0; i < m_CellIndices.size(); i++)
	{
		if (gridManager.GetCell(m_CellIndices[i]).isTriggered)
		{
			if (!m_IsSteppedOn[i])
			{
				m_IsSteppedOn[i] = true;
				if (gridManager.GetCell(m_CellIndices[i]).pActor.lock())
					ServiceLocator::GetSoundManager()->PlayEffect("Sounds/StepOnBurger.mp3", GameData::SoundeffectVolume, 0, false);
			}

			if (auto actor = gridManager.GetCell(m_CellIndices[i]).pActor.lock())
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
	auto& gridManager = GridManager::GetInstance();
	auto elapsedTime = Timer::GetInstance().GetElapsed();

	auto pos = m_pGameObject.lock()->GetTransform().GetPosition();
	m_FallVelocity += m_FallAcceleration * elapsedTime;
	pos.y -= m_FallVelocity * elapsedTime;
	m_pGameObject.lock()->GetTransform().SetPosition(pos.x, pos.y, 0.f);

	if (auto idx = gridManager.PositionToIndex({ pos.x, pos.y }); std::find(m_CellIndices.begin(), m_CellIndices.end(), idx) == m_CellIndices.end())
	{
		auto& cell = gridManager.GetCell(idx);
		if (pos.y + cell.boundingbox.h > Renderer::GetInstance().GetWindowHeight() || gridManager.GetCell({ pos.x, float(pos.y + cell.boundingbox.h) }).isTriggered)
		{
			m_OnPlate = true;
			cell.isTriggered = true;
			return;
		}

		if (!cell.isBurgerPlatform) return;

		if (pos.y < cell.boundingbox.y)
		{
			for (int i = 0; i < m_IsSteppedOn.size(); ++i) m_IsSteppedOn[i] = false;
			m_CellIndices.clear();
			m_CellIndices = { idx, idx + 1, idx + 2, idx + 3 };
			m_FallVelocity = 0.f;
			m_IsDropping = false;
			m_NextPlatformTriggered = true;
			for (int i = 0; i < m_BurgerPieces; i++)
				gridManager.GetCell(idx + i).isTriggered = true;
		}
	}
}