#include "pch.h"
#include "Level02Scene.h"
#include "Base/Helpers.h"

#pragma region Component Includes
#include "Components/PeterPepperComponent.h"
#include "Components/HealthDisplayComponent.h"
#include "Components/ScoreDisplayComponent.h"
#include "Components/BurgerComponent.h"
#include "Components/EnemySpawnerComponent.h"
#pragma endregion

#include "LevelParser/LevelParser.h"
#include "Command/PlayerCommands.h"
#include "Singletons/GameState.h"

void Level02Scene::Initialize()
{
	LoadLevel();
	LoadPlayers();
	LoadHUD();
}
void Level02Scene::Update()
{
	if (GameState::GetInstance().LevelCompleted())
	{
		HandleWinState();
	}
	else if (GameState::GetInstance().PlayerKilled())
	{
		HandleKillState();
	}
}

void Level02Scene::OnSceneActivated()
{
	auto& gameState = GameState::GetInstance();
	gameState.OnReset(gameState.GetGameMode());
	gameState.SetNrOfSlices(FindNumObjectsWithTag("BurgerSlice"));


	m_pP1.lock()->GetTransform().SetPosition({ m_P1SpawnPos.x, m_P1SpawnPos.y, 0 });
	m_pP1.lock()->GetComponent<PeterPepperComponent>()->AddScore(gameState.GetScoreP1());
	if (gameState.GetGameMode() == GameMode::COOP)
	{
		m_pP2.lock()->Enable();
		m_pP2.lock()->GetTransform().SetPosition(m_P2SpawnPos.x, m_P2SpawnPos.y, 0);
		m_pP2.lock()->GetComponent<PeterPepperComponent>()->AddScore(gameState.GetScoreP2());
	}

	ServiceLocator::GetSoundManager()->PlayStream("Sounds/Start.mp3", GameData::SoundtrackVolume, false);
	ServiceLocator::GetSoundManager()->PlayStream("Sounds/LevelTheme02.mp3", GameData::SoundtrackVolume, true);
}
void Level02Scene::OnSceneDeactivated()
{
	ServiceLocator::GetSoundManager()->StopStream();
	GameState::GetInstance().SetScoreP1(m_pP1.lock()->GetComponent<PeterPepperComponent>()->GetScore());
	if (GameState::GetInstance().GetGameMode() == GameMode::COOP)
	{
		GameState::GetInstance().SetScoreP2(m_pP2.lock()->GetComponent<PeterPepperComponent>()->GetScore());
	}
}

void Level02Scene::HandleWinState()
{
	m_ElapsedTimeSinceWin += Timer::GetInstance().GetElapsed();
	if (m_ElapsedTimeSinceWin > m_NextLevelWaitTime)
	{
		SceneManager::GetInstance().SetActiveScene("Level03Scene");
		m_ElapsedTimeSinceWin = 0.f;
	}

	if (!m_pP1.expired())
	{
		m_pP1.lock()->GetComponent<PeterPepperComponent>()->SetState(State::win, Direction::none);
	}
	if (!m_pP2.expired())
	{
		m_pP2.lock()->GetComponent<PeterPepperComponent>()->SetState(State::win, Direction::none);
	}
}
void Level02Scene::HandleKillState()
{
	m_ElapsedTimeSinceKill += Timer::GetInstance().GetElapsed();
	if (m_ElapsedTimeSinceKill > m_LevelReloadWaitTime)
	{
		if (m_pP1.lock()->GetComponent<PeterPepperComponent>()->GetLives() == 0)
		{
			SceneManager::GetInstance().SetActiveScene("DefeatScene");
		}

		RemoveObjectsWithTag("Enemy");
		m_pP1.lock()->GetTransform().SetPosition(m_P1SpawnPos.x, m_P1SpawnPos.y, 0.f);
		m_pP2.lock()->GetTransform().SetPosition(m_P2SpawnPos.x, m_P2SpawnPos.y, 0.f);
		m_ElapsedTimeSinceKill = 0.f;

		GameState::GetInstance().OnRespawn();
		ServiceLocator::GetSoundManager()->PlayStream("Sounds/LevelTheme02.mp3", GameData::SoundtrackVolume, true);
	}

	m_pP1.lock()->GetComponent<PeterPepperComponent>()->SetState(State::dead, Direction::none);
}

void Level02Scene::LoadLevel()
{
	// Read in level data
	LevelData data{};
	LevelParser::ParseLevel(GameData::StringPathLvl02, GameData::GameScale, data);

	auto levelGO = Add(std::make_shared<GameObject>());
	levelGO->GetTransform().SetScale(GameData::GameScale);
	levelGO->GetTransform().SetPosition(0.f, 32.f, 0.f);
	levelGO->AddComponent<TextureComponent>(data.backgroundFileName);
	levelGO->AddComponent<RenderComponent>();
	auto grid = levelGO->AddComponent<GridComponent>(data.gridCells, data.nrOfRows, data.nrOfCols);

	std::vector<glm::vec3> enemySpawnPositions{};
	for (size_t i = 0; i < data.enemySpawnCellIndices.size(); ++i)
	{
		auto pos = grid->IndexToPosition(data.enemySpawnCellIndices[i]);
		if (pos.x > Renderer::GetInstance().GetWindowWidth() / 2.f)
			pos.x += GameData::EnemySpawnOffset;
		else
			pos.x -= GameData::EnemySpawnOffset;
		enemySpawnPositions.emplace_back(glm::vec3{ pos.x, pos.y, 0.f });
	}

	levelGO->AddComponent<EnemySpawnerComponent>(enemySpawnPositions, data.maxEnemies);
	levelGO->SetTag("Level");

	std::for_each(data.burgers.begin(), data.burgers.end(), [&](const std::shared_ptr<GameObject>& burger) { Add(burger); });

	m_P1SpawnPos = grid->IndexToPosition(data.playerSpawnCellIndices[0]);
	m_P2SpawnPos = grid->IndexToPosition(data.playerSpawnCellIndices[1]);
}
void Level02Scene::LoadPlayers()
{
	m_pP1 = Helpers::AddPlayer(shared_from_this(), PlayerID::PLAYERONE);
	m_pP1.lock()->GetTransform().SetScale(4.f);

	m_pP2 = Helpers::AddPlayer(shared_from_this(), PlayerID::PLAYERTWO);
	m_pP2.lock()->GetTransform().SetScale(4.f);
	m_pP2.lock()->Disable();
}
void Level02Scene::LoadHUD()
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);

	auto child = std::make_shared<GameObject>();
	child->AddComponent<TextComponent>(font);
	child->AddComponent<RenderComponent>();
	child->AddComponent<FPSComponent>();
	Add(child);
}