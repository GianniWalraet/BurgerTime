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
	if (m_pGrid.expired()) return;

	if (m_NextPlatformTriggered)
	{
		for (int i = 0; i < static_cast<int>(m_CellIndices.size()); i++)
		{
			if (auto pActor = m_pGrid.lock()->GetCell(m_CellIndices[i]).pActor; !pActor.expired())
			{
				pActor.lock()->GetComponent<PeterPepperComponent>()->AddScore(m_ScoreFromBurgers);
				m_ScoreFromBurgers = 0;
			}
			m_pGrid.lock()->GetCell(m_CellIndices[i]).isTriggered = false;
			m_pGrid.lock()->GetCell(m_CellIndices[i]).pActor = std::weak_ptr<GameObject>();
			ServiceLocator::GetSoundManager()->PlayEffect("Sounds/BurgerCollide.mp3", GameData::SoundeffectVolume, 0, false);
		}

		m_NextPlatformTriggered = false;
	}

	if (!m_IsDropping) CheckCanDrop();
	else HandleBurgerDropping();
}

void BurgerComponent::CheckCanDrop()
{
	for (size_t i = 0; i < m_CellIndices.size(); i++)
	{
		if (m_pGrid.lock()->GetCell(m_CellIndices[i]).isTriggered)
		{
			if (!m_IsSteppedOn[i])
			{
				m_IsSteppedOn[i] = true;
				if (m_pGrid.lock()->GetCell(m_CellIndices[i]).pActor.lock())
					ServiceLocator::GetSoundManager()->PlayEffect("Sounds/StepOnBurger.mp3", GameData::SoundeffectVolume, 0, false);
			}

			if (auto actor = m_pGrid.lock()->GetCell(m_CellIndices[i]).pActor.lock())
			{
				m_pTriggerActor = actor->GetComponent<PeterPepperComponent>();
			}
		}
	}
	if (std::all_of(m_IsSteppedOn.begin(), m_IsSteppedOn.end(), [](bool v) { return v; }))
	{
		m_IsDropping = true;
		if (m_pTriggerActor.lock())
		{
			m_pTriggerActor.lock()->OnBurgerDropped();
		}
	}
}
void BurgerComponent::HandleBurgerDropping()
{
	ApplyFallAcceleration();
	CheckEnemyCollision();

	auto& transform = m_pGameObject.lock()->GetTransform();
	auto pos = transform.GetPosition();

	auto idx = m_pGrid.lock()->PositionToIndex({ pos.x, pos.y });
	if (std::find(m_CellIndices.begin(), m_CellIndices.end(), idx) != m_CellIndices.end())
		return;

	if (CheckOnPlate(idx)) return;

	auto cell = m_pGrid.lock()->GetCell(idx);
	if (cell.isBurgerPlatform)
	{
		if (pos.y > cell.boundingbox.y)
		{
			transform.SetPosition(pos.x, float(cell.boundingbox.y), pos.z);
			for (int i = 0; i < static_cast<int>(m_IsSteppedOn.size()); ++i) m_IsSteppedOn[i] = false;
			m_CellIndices.clear();
			m_CellIndices = { idx, idx + 1, idx + 2, idx + 3 };
			m_FallVelocity = m_DefaultFallVelocity;
			m_IsDropping = false;

			for (int i = 0; i < static_cast<int>(m_CellIndices.size()); i++)
			{
				m_pGrid.lock()->GetCell(m_CellIndices[i]).isTriggered = true;
				m_pGrid.lock()->GetCell(m_CellIndices[i]).pActor = m_pTriggerActor.lock()->GetGameObject().lock();
			}
			m_NextPlatformTriggered = true;
		}
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
void BurgerComponent::CheckEnemyCollision()
{
	const auto& pos = m_pGameObject.lock()->GetTransform().GetPosition();
	auto enemies = m_pGameObject.lock()->GetScene()->FindObjectsWithTag("Enemy");
	auto burgerPieceSize = GameData::BurgerPieceSize * GameData::GameScale;
	for (const auto& enemy : enemies)
	{
		auto burgerCollider = Rectf(pos.x, pos.y, burgerPieceSize * m_NumBurgerPieces, burgerPieceSize);
		auto enemyCollider = enemy->GetComponent<Box2DComponent>()->GetCollider();
		auto enemyPos = enemy->GetTransform().GetPosition();
		if (utils::IsPointInRect(Point2f{enemyPos.x, enemyPos.y - GameData::BurgerPieceSize}, burgerCollider))
		{
			enemy->GetScene()->Remove(enemy);
			if (m_ScoreFromBurgers == 0) m_ScoreFromBurgers = m_DefaultScore;
			else m_ScoreFromBurgers *= 2;
		}

	}
}
bool BurgerComponent::CheckOnPlate(int cellIdx)
{
	const auto& pGrid = m_pGrid.lock();
	auto pos = m_pGameObject.lock()->GetTransform().GetPosition();

	auto& cell = pGrid->GetCell(cellIdx);
	auto& cellBelow = pGrid->GetCell(cellIdx + pGrid->GetNrCols());
	if (cell.isPlate || cellBelow.hasBurger)
	{
		m_OnPlate = true;
		cell.hasBurger = true;
		m_pGameObject.lock()->GetTransform().SetPosition(pos.x, float(cell.boundingbox.y), pos.z);
		GameState::GetInstance().OnSliceCompleted();
		return true;
	}

	return false;
}