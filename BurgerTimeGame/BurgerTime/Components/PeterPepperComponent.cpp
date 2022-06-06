 #include "pch.h"
#include "PeterPepperComponent.h"
#include "Observer/AchievementObserver.h"
#include "Components/PeterPepperComponent.h"
#include "Components/GridComponent.h"
#include "Components/EnemyComponent.h"
#include "Singletons/GameState.h" 

PeterPepperComponent::PeterPepperComponent(int8_t lives)
	: m_Lives{ lives }
{
}

void PeterPepperComponent::AddCloseEnemy(EnemyComponent* pComp)
{
	m_pCloseEnemies.emplace_back(pComp);
}
void PeterPepperComponent::RemoveCloseEnemy(EnemyComponent* pComp)
{
	m_pCloseEnemies.erase(std::remove(m_pCloseEnemies.begin(), m_pCloseEnemies.end(), pComp), m_pCloseEnemies.end());
}

void PeterPepperComponent::Initialize()
{
	m_pSpriteComponent = m_pGameObject.lock()->GetComponent<SpriteComponent>();
	if (auto lvl = m_pGameObject.lock()->GetScene()->FindObjectWithTag("Level"))
	{
		m_pGrid = lvl->GetComponent<GridComponent>();
	}
}
void PeterPepperComponent::Update()
{
	if (!HandleState())
	{
		m_State = State::idle;
	}

	if (m_IsStunned)
	{
		m_TimeSinceStun += Timer::GetInstance().GetElapsed();
		if (m_TimeSinceStun > m_MaxStunnedTime)
		{
			m_TimeSinceStun = 0.f;
			m_IsStunned = false;
		}
	}
	else
	{
		HandleEnemyCollisions();
		HandleCellCollision();
	}
}

void PeterPepperComponent::OnDie()
{
	if (m_Lives == 0 || m_IsStunned) return;

	--m_Lives;

	m_IsStunned = true;
	m_pCloseEnemies.clear();
	GameState::GetInstance().OnPlayerKill();

	NotifyAll(Event::PlayerDied);
	if (m_Score < 0) m_Score = 0;
}
void PeterPepperComponent::OnBurgerDropped()
{
	if (m_Lives == 0) return;
	ServiceLocator::GetSoundManager()->PlayEffect("Sounds/ScoreGain.mp3", GameData::SoundeffectVolume, 0, false);

	m_Score += m_ScoreGain;

	NotifyAll(Event::BurgerDropped);
	if (m_Score >= 500)
	{
		AchievementObserver::GetInstance().Notify(EAchievements::GameWin);
	}
}
void PeterPepperComponent::OnLevelWin()
{

}

bool PeterPepperComponent::HandleState()
{
	if (m_State == m_PrevState && m_Dir == m_PrevDir) return false;

	SDL_Rect source{};
	int rows{1}, cols{1};
	bool mirror{};
	float frameSec = 1 / 15.f;
	switch (m_State)
	{
	case State::moveHorizontal:
		source.x = GameData::SpriteCellSize * 3;
		source.y = 0;
		source.w = GameData::SpriteCellSize * 3;
		source.h = GameData::SpriteCellSize;

		rows = 1;
		cols = 3;

		mirror = m_Dir == Direction::right;
		break;

	case State::moveVertical:
		if (m_Dir == Direction::up)
		{
			source.x = GameData::SpriteCellSize * 6;
			source.y = 0;
			source.w = GameData::SpriteCellSize * 3;
			source.h = GameData::SpriteCellSize;

			rows = 1;
			cols = 3;
		}
		else
		{
			source.x = 0;
			source.y = 0;
			source.w = GameData::SpriteCellSize * 3;
			source.h = GameData::SpriteCellSize;

			rows = 1;
			cols = 3;
		}
		break;

	case State::idle:
	{
		switch (m_Dir)
		{
		case Direction::left:
			source.x = GameData::SpriteCellSize * 4;
			source.y = 0;
			source.w = GameData::SpriteCellSize;
			source.h = GameData::SpriteCellSize;
			break;
		case Direction::right:
			source.x = GameData::SpriteCellSize * 4;
			source.y = 0;
			source.w = GameData::SpriteCellSize;
			source.h = GameData::SpriteCellSize;

			mirror = true;
			break;
		case Direction::up:
			source.x = GameData::SpriteCellSize * 7;
			source.y = 0;
			source.w = GameData::SpriteCellSize;
			source.h = GameData::SpriteCellSize;
			break;
		case Direction::down:
			source.x = GameData::SpriteCellSize;
			source.y = 0;
			source.w = GameData::SpriteCellSize;
			source.h = GameData::SpriteCellSize;
			break;
		}
	}
		break;
	case State::dead:
		rows = 1;
		cols = 6;
		frameSec = 1 / 1.5f;
		source.x = GameData::SpriteCellSize * 3;
		source.y = GameData::SpriteCellSize;
		source.w = GameData::SpriteCellSize * 6;
		source.h = GameData::SpriteCellSize;
		break;
	case State::win:
		rows = 1;
		cols = 3;

		source.x = 0;
		source.y = GameData::SpriteCellSize;
		source.w = GameData::SpriteCellSize * 3;
		source.h = GameData::SpriteCellSize;
		break;
	}

	m_pSpriteComponent->Reset(source, rows, cols, mirror, frameSec);

	m_PrevState = m_State;
	m_PrevDir = m_Dir;
	return true;
}
void PeterPepperComponent::HandleCellCollision()
{
	auto& pos = m_pGameObject.lock()->GetTransform().GetPosition();
	m_CellIdx = m_pGrid->PositionToIndex({ pos.x, pos.y });

	if (m_CellIdx != m_PrevCellIdx)
	{
		m_pGrid->GetCell(m_CellIdx).isTriggered = true;
		m_pGrid->GetCell(m_CellIdx).pActor = m_pGameObject.lock();
		m_pGrid->GetCell(m_PrevCellIdx).isTriggered = false;
	}
	m_PrevCellIdx = m_CellIdx;
}

void PeterPepperComponent::HandleEnemyCollisions()
{
	for (const auto& enemy : m_pCloseEnemies)
	{
		if (enemy)
		{
			auto pos = m_pGameObject.lock()->GetTransform().GetPosition();
			auto otherPos = enemy->GetGameObject().lock()->GetTransform().GetPosition();

			if (utils::Distance(pos, otherPos) < m_KillRadius)
			{
				OnDie();
			}
		}
	}
}