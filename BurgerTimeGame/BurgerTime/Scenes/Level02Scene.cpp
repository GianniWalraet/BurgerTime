#include "pch.h"
#include "Level02Scene.h"
#include "Base/Helpers.h"

#pragma region Component Includes
#include "Components/PeterPepperComponent.h"
#include "Components/HealthDisplayComponent.h"
#include "Components/ScoreDisplayComponent.h"
#include "Components/BurgerComponent.h"
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

	}
}

void Level02Scene::OnSceneActivated()
{
	auto& gameState = GameState::GetInstance();
	if(!m_pP1.expired()) m_pP1.lock()->GetTransform().SetPosition({ 30, 80, 0 });

	if (gameState.GetGameMode() == GameMode::MULTIPLAYER)
	{
		if (!m_pP2.expired())
		{
			m_pP2.lock()->Enable();
			m_pP2.lock()->GetTransform().SetPosition(30, 160, 0);
		}
	}
	else
	{
		if (!m_pP2.expired())
		{
			m_pP2.lock()->Disable();
		}
	}

	ServiceLocator::GetSoundManager()->PlayStream("Sounds/Start.mp3", GameData::SoundtrackVolume, false);
	ServiceLocator::GetSoundManager()->PlayStream("Sounds/LevelTheme02.mp3", GameData::SoundtrackVolume, true);
}
void Level02Scene::OnSceneDeactivated()
{
	ServiceLocator::GetSoundManager()->StopStream();
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
	levelGO->SetTag("Level");

	std::for_each(data.burgers.begin(), data.burgers.end(), [&](const std::shared_ptr<GameObject>& burger) { Add(burger); });

	m_P1SpawnPos = grid->IndexToPosition(data.playerSpawnCellIndices[0]);
	m_P2SpawnPos = grid->IndexToPosition(data.playerSpawnCellIndices[1]);
}
void Level02Scene::LoadPlayers()
{
	m_pP1 = Helpers::CreatePlayer(shared_from_this(), PlayerID::PLAYERONE);
	m_pP1.lock()->GetTransform().SetScale(4.f);

	m_pP2 = Helpers::CreatePlayer(shared_from_this(), PlayerID::PLAYERTWO);
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