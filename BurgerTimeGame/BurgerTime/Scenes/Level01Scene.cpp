#include "pch.h"
#include "Level01Scene.h"
#include "Base/Helpers.h"

#pragma region Component Includes
#include "Components/BurgerComponent.h"
#include "Components/GridComponent.h"
#include "Components/MrHotDogComponent.h"
#include "Components/EnemySpawnerComponent.h"
#pragma endregion

#include "LevelParser/LevelParser.h"
#include "Command/PlayerCommands.h"
#include "Singletons/GameState.h"


void Level01Scene::Initialize()
{
	LoadLevel();
	LoadPlayers();
	LoadHUD();
}
void Level01Scene::Update()
{
	if (GameState::GetInstance().LevelCompleted())
	{
		SceneManager::GetInstance().SetActiveScene("Level02Scene");
	}
}

void Level01Scene::OnSceneActivated()
{
	auto& gameState = GameState::GetInstance();
	m_pP1.lock()->GetTransform().SetPosition({ m_P1SpawnPos.x, m_P1SpawnPos.y, 0 });

	gameState.Reset(gameState.GetGameMode());
	gameState.SetNrOfSlices(FindNumObjectsWithTag("BurgerSlice"));

	if (gameState.GetGameMode() == GameMode::MULTIPLAYER)
	{
		m_pP2.lock()->Enable();
		m_pP2.lock()->GetTransform().SetPosition(m_P2SpawnPos.x, m_P2SpawnPos.y, 0);
	}
	else
	{
		m_pP2.lock()->Disable();
	}

	ServiceLocator::GetSoundManager()->PlayStream("Sounds/Start.mp3", GameData::SoundtrackVolume, false);
	ServiceLocator::GetSoundManager()->PlayStream("Sounds/LevelTheme01.mp3", GameData::SoundtrackVolume, true);
}
void Level01Scene::OnSceneDeactivated()
{
	ServiceLocator::GetSoundManager()->StopStream();
}

void Level01Scene::LoadLevel()
{
	// Read in level data
	LevelData data{};
	LevelParser::ParseLevel(GameData::StringPathLvl01, GameData::GameScale, data);

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
		if (pos.x > Renderer::GetInstance().GetWindowWidth())
			pos.x += GameData::EnemySpawnOffset * 3.f;
		else
			pos.x -= GameData::EnemySpawnOffset * 3.f;
		enemySpawnPositions.emplace_back(glm::vec3{ pos.x, pos.y, 0.f });
	}

	levelGO->AddComponent<EnemySpawnerComponent>(enemySpawnPositions, data.maxEnemies);
	levelGO->SetTag("Level");


	std::for_each(data.burgers.begin(), data.burgers.end(), [&](const std::shared_ptr<GameObject>& burger) { Add(burger); });

	m_P1SpawnPos = grid->IndexToPosition(data.playerSpawnCellIndices[0]);
	m_P2SpawnPos = grid->IndexToPosition(data.playerSpawnCellIndices[1]);
}
void Level01Scene::LoadPlayers()
{
	m_pP1 = Helpers::AddPlayer(shared_from_this(), PlayerID::PLAYERONE);
	m_pP1.lock()->GetTransform().SetScale(GameData::GameScale);

	m_pP2 = Helpers::AddPlayer(shared_from_this(), PlayerID::PLAYERTWO);
	m_pP2.lock()->GetTransform().SetScale(GameData::GameScale);
	m_pP2.lock()->Disable();
}
void Level01Scene::LoadHUD()
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);

	auto child = std::make_shared<GameObject>();
	child->AddComponent<TextComponent>(font, "60", glm::vec2{0.5f, 0.f});
	child->AddComponent<RenderComponent>();
	child->AddComponent<FPSComponent>();
	child->GetTransform().SetPosition(Renderer::GetInstance().GetWindowWidth() / 2.f, 0.f, 0.f);
	Add(child);
}
