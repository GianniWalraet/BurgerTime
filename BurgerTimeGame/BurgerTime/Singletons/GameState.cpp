#include "pch.h"
#include "GameState.h"


void GameState::OnReset(GameMode newState)
{
	m_GameMode = newState;
	m_NumBurgerSlices = 0;
	m_LevelComplete = false;
	m_PlayerKilled = false;
	InputManager::GetInstance().EnableInput();
}
void GameState::OnRespawn()
{
	m_LevelComplete = false;
	m_PlayerKilled = false;
	InputManager::GetInstance().EnableInput();
}

void GameState::OnSliceCompleted()
{
	--m_NumBurgerSlices;

	if (m_NumBurgerSlices == 0)
	{
		m_LevelComplete = true;
		ServiceLocator::GetSoundManager()->StopStream();
		ServiceLocator::GetSoundManager()->PlayEffect("Sounds/End.mp3", GameData::SoundeffectVolume, 0, false);
		InputManager::GetInstance().DisableInput();
	}
}
void GameState::OnPlayerKill()
{
	m_PlayerKilled = true;
	ServiceLocator::GetSoundManager()->StopStream();
	ServiceLocator::GetSoundManager()->PlayEffect("Sounds/LoseLife.mp3", GameData::SoundeffectVolume, 0, false);
	InputManager::GetInstance().DisableInput();
}
