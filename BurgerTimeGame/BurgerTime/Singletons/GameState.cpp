#include "pch.h"
#include "GameState.h"


void GameState::OnSliceCompleted()
{
	--m_NumBurgerSlices;

	if (m_NumBurgerSlices == 0)
	{
		OnGameWin();
	}
}

void GameState::OnGameWin()
{

}

void GameState::OnGameLoss()
{

}