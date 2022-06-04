#include "pch.h"
#include "BurgerComponent.h"

BurgerComponent::BurgerComponent(const std::vector<int>& cellIndices)
	:m_CellIndices(cellIndices)
{
	
}

void BurgerComponent::Update()
{
	auto& gridManager = GridManager::GetInstance();

	for (size_t i = 0; i < m_CellIndices.size(); i++)
	{
		if (gridManager.GetCell(m_CellIndices[i]).isTriggered)
		{
			m_IsSteppedOn[i] = true;
		}
	}

	if (std::all_of(m_IsSteppedOn.begin(), m_IsSteppedOn.end(), [](bool v) { return v; }))
	{
		auto pos = m_pGameObject.lock()->GetTransform().GetPosition();
		pos.y -= 10 * Timer::GetInstance().GetElapsed();
		m_pGameObject.lock()->GetTransform().SetPosition(pos.x, pos.y, 0.f);
	}
}