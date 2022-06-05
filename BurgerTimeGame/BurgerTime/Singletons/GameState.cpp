#include "pch.h"
#include "GameState.h"


void GameState::Reset(GameMode newState)
{
	m_GameMode = newState;
	m_NumBurgerSlices = 0;
	m_LevelComplete = false;
}

void GameState::OnSliceCompleted()
{
	--m_NumBurgerSlices;

	if (m_NumBurgerSlices == 0)
	{
		m_LevelComplete = true;
	}
}

void GameState::OnGameLoss()
{

}