#include "pch.h"
#include "PeterPepperComponent.h"
#include "Observer/AchievementObserver.h"

const int g_GridSize{ 16 };

PeterPepperComponent::PeterPepperComponent()
	: m_Lives{3}
{
}

PeterPepperComponent::~PeterPepperComponent()
{

}

void PeterPepperComponent::Initialize()
{
	m_pSpriteComponent = m_pGameObject.lock()->GetComponent<SpriteComponent>();
}

void PeterPepperComponent::Update()
{
	if (!HandleState())
	{
		m_State = State::idle;
	}

	auto& gridManager = GridManager::GetInstance();
	auto& pos = m_pGameObject.lock()->GetTransform().GetPosition();
	m_CellIdx = gridManager.PositionToIndex({ pos.x, pos.y });

	std::cout << gridManager.PositionToIndex({ pos.x, pos.y }) << '\n';

	if (m_CellIdx != m_PrevCellIdx)
	{
		gridManager.GetCell(m_CellIdx).isTriggered = true;
		gridManager.GetCell(m_PrevCellIdx).isTriggered = false;
	}
	m_PrevCellIdx = m_CellIdx;
}

void PeterPepperComponent::OnDie()
{
	if (m_Lives == 0) return;

	--m_Lives;
	m_Score -= m_ScoreLoss;
	ServiceLocator::GetSoundManager()->PlayEffect("Sounds/LoseLife.mp3", 50);

	if (m_Score < 0) m_Score = 0;

	NotifyAll(Event::PlayerDied);
}
void PeterPepperComponent::OnBurgerDropped()
{
	if (m_Lives == 0) return;

	m_Score += m_ScoreGain;

	ServiceLocator::GetSoundManager()->PlayEffect("Sounds/ScoreGain.mp3", 50, 0, false);
	NotifyAll(Event::BurgerDropped);

	if (m_Score >= 500 && !m_HasWon)
	{
		AchievementObserver::GetInstance().Notify(EAchievements::GameWin);
		m_HasWon = true;
	}
}

bool PeterPepperComponent::HandleState()
{
	if (m_State == m_PrevState && m_Dir == m_PrevDir) return false;

	SDL_Rect source{};
	int rows{1}, cols{1};
	bool mirror{};

	switch (m_State)
	{
	case State::moveHorizontal:
		source.x = g_GridSize * 3;
		source.y = 0;
		source.w = g_GridSize * 3;
		source.h = g_GridSize;

		rows = 1;
		cols = 3;

		mirror = m_Dir == Direction::right;
		break;

	case State::moveVertical:
		if (m_Dir == Direction::up)
		{
			source.x = g_GridSize * 6;
			source.y = 0;
			source.w = g_GridSize * 3;
			source.h = g_GridSize;

			rows = 1;
			cols = 3;
		}
		else
		{
			source.x = 0;
			source.y = 0;
			source.w = g_GridSize * 3;
			source.h = g_GridSize;

			rows = 1;
			cols = 3;
		}
		break;

	case State::idle:
	{
		switch (m_Dir)
		{
		case Direction::left:
			source.x = g_GridSize * 4;
			source.y = 0;
			source.w = g_GridSize;
			source.h = g_GridSize;
			break;
		case Direction::right:
			source.x = g_GridSize * 4;
			source.y = 0;
			source.w = g_GridSize;
			source.h = g_GridSize;

			mirror = true;
			break;
		case Direction::up:
			source.x = g_GridSize * 7;
			source.y = 0;
			source.w = g_GridSize;
			source.h = g_GridSize;
			break;
		case Direction::down:
			source.x = g_GridSize;
			source.y = 0;
			source.w = g_GridSize;
			source.h = g_GridSize;
			break;
		}
	}
		break;
	case State::dead:
		break;
	}

	m_pSpriteComponent->Reset(source, rows, cols, mirror);

	m_PrevState = m_State;
	m_PrevDir = m_Dir;
	return true;
}