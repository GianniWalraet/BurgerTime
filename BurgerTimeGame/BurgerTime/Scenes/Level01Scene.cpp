#include "pch.h"
#include "Level01Scene.h"

#pragma region Component Includes
#include "Components/PeterPepperComponent.h"
#include "Components/HealthDisplayComponent.h"
#include "Components/ScoreDisplayComponent.h"
#include "Components/BurgerComponent.h"
#pragma endregion

#include "LevelParser/LevelParser.h"
#include "Command/PlayerCommands.h"

void Level01Scene::Initialize()
{
	LoadLevel();
	LoadPlayers();
	LoadHUD();
}
void Level01Scene::Update()
{
	
}

void Level01Scene::OnSceneActivated()
{
	ServiceLocator::GetSoundManager()->PlayStream("Sounds/Start.mp3", GameData::SoundtrackVolume, false);
	ServiceLocator::GetSoundManager()->PlayStream("Sounds/MainTheme.mp3", GameData::SoundtrackVolume, true);
}
void Level01Scene::OnSceneDeactivated()
{
	ServiceLocator::GetSoundManager()->StopStream();
}

void Level01Scene::LoadLevel()
{
	auto& gridManager = GridManager::GetInstance();

	// Read in level data
	std::string lvlTexFile;
	int nrRows, nrCols;
	std::vector<Cell> cells;
	std::vector<std::shared_ptr<GameObject>> burgers;
	LevelParser::ParseLevel(GameData::StringPathLvl01, GameData::GameScale, lvlTexFile, nrRows, nrCols, cells, burgers);

	auto LvlTextureGO = std::make_shared<GameObject>();
	LvlTextureGO->GetTransform().SetScale(GameData::GameScale);
	LvlTextureGO->GetTransform().SetPosition(0.f, 32.f, 0.f);
	LvlTextureGO->AddComponent<TextureComponent>(lvlTexFile);
	LvlTextureGO->AddComponent<RenderComponent>();
	Add(LvlTextureGO);

	gridManager.SetGrid(cells, nrRows, nrCols);
	std::for_each(burgers.begin(), burgers.end(), [&](const std::shared_ptr<GameObject>& burger) { Add(burger); });
}
void Level01Scene::LoadPlayers()
{
	AddPlayer(0, { 50, 100, 0 }, 4.f);
}
void Level01Scene::LoadHUD()
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);

	auto child = std::make_shared<GameObject>();
	child->AddComponent<TextComponent>(font);
	child->AddComponent<RenderComponent>();
	child->AddComponent<FPSComponent>();
	Add(child);
}

void Level01Scene::AddPlayer(int playerID, const glm::vec3& pos, float scale)
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);

	int gridBoxSize{ 16 };
	SDL_Rect source{};
	source.x = gridBoxSize * 3;
	source.y = 0;
	source.w = gridBoxSize * 3;
	source.h = gridBoxSize;

	// Peter Pepper
	auto pp = std::make_shared<GameObject>();
	pp->AddComponent<PeterPepperComponent>();
	pp->AddComponent<SpriteComponent>("BurgerTimeSprite.png", 3, 1, 1.f / 15.f, glm::vec2{ 0.5f, 1.f }, source);
	pp->AddComponent<RenderComponent>();
	pp->AddComponent<Box2DComponent>(float(gridBoxSize), float(gridBoxSize), true);
	pp->AddComponent<ControllerComponent>(glm::vec2{ 150.f, 100.f });
	auto ppComp = pp->GetComponent<PeterPepperComponent>();

	pp->GetTransform().SetPosition(pos);
	pp->GetTransform().SetScale(scale);
	Add(pp);

	// Health display
	auto hd = std::make_shared<GameObject>();
	auto hdComp = hd->AddComponent<HealthDisplayComponent>(ppComp);
	ppComp->AddObserver(hdComp);

	hd->GetTransform().SetScale(4.f);
	Add(hd);

	auto sd = std::make_shared<GameObject>();
	auto txtComp = sd->AddComponent<TextComponent>(ResourceManager::GetInstance().LoadFont("origa___.ttf", 30));
	sd->AddComponent<RenderComponent>();
	auto sdComp = sd->AddComponent<ScoreDisplayComponent>(ppComp, txtComp);
	ppComp->AddObserver(sdComp);

	Add(sd);

	InputManager::GetInstance().AddCommand<MoveLeftCommand>(playerID, pp, ControllerButton::GAMEPAD_DPAD_LEFT);
	InputManager::GetInstance().AddCommand<MoveRightCommand>(playerID, pp, ControllerButton::GAMEPAD_DPAD_RIGHT);
	InputManager::GetInstance().AddCommand<MoveUpCommand>(playerID, pp, ControllerButton::GAMEPAD_DPAD_UP);
	InputManager::GetInstance().AddCommand<MoveDownCommand>(playerID, pp, ControllerButton::GAMEPAD_DPAD_DOWN);

	// keyboard commands for debug testing
#ifdef _DEBUG
	InputManager::GetInstance().AddCommand<KillCommand>(pp, SDLK_j, InputState::down);
	InputManager::GetInstance().AddCommand<ScoreCommand>(pp, SDLK_k, InputState::down);
	InputManager::GetInstance().AddCommand<MoveLeftCommand>(pp, SDLK_a);
	InputManager::GetInstance().AddCommand<MoveRightCommand>(pp, SDLK_d);
	InputManager::GetInstance().AddCommand<MoveUpCommand>(pp, SDLK_w);
	InputManager::GetInstance().AddCommand<MoveDownCommand>(pp, SDLK_s);
#endif
}
