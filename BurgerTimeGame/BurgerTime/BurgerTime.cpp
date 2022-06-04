#include "pch.h"
#include "BurgerTime.h"

// Component includes
#include "Components/PeterPepperComponent.h"
#include "Components/HealthDisplayComponent.h"
#include "Components/ScoreDisplayComponent.h"
#include "Components/BurgerComponent.h"

// Prefab includes
#include "Prefabs/PeterPepper.h"

// Other
#include "LevelParser/LevelParser.h"
#include "Command/PlayerCommands.h"

void BurgerTime::LoadGame() const
{
#ifdef _DEBUG
	ServiceLocator::RegisterSoundManager(std::make_shared<SoundManager>());
	ServiceLocator::RegisterSoundManager(std::make_shared<LoggedSoundManager>(ServiceLocator::GetSoundManager()));
#else
	ServiceLocator::RegisterSoundManager(std::make_shared<SoundManager>());

#endif

	PrintGameInfo();

	auto& scene = SceneManager::GetInstance().CreateScene("Level01");
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);

	// level
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
		scene.Add(LvlTextureGO);

		gridManager.SetGrid(cells, nrRows, nrCols);
		std::for_each(burgers.begin(), burgers.end(), [&](const std::shared_ptr<GameObject>& burger) { scene.Add(burger); });
	}

	// FPS Counter
	{
		auto child = std::make_shared<GameObject>();
		child->AddComponent<TextComponent>(font);
		child->AddComponent<RenderComponent>();
		child->AddComponent<FPSComponent>();
		scene.Add(child);
	}

	// Players
	{
		AddPlayer(scene, { 50, 100, 0 }, 4.f);
	}

	ServiceLocator::GetSoundManager()->PlayStream("Sounds/Start.mp3", GameData::SoundtrackVolume, false);
	ServiceLocator::GetSoundManager()->PlayStream("Sounds/MainTheme.mp3", GameData::SoundtrackVolume, true);
}

void BurgerTime::PrintGameInfo() const
{
	std::cout << "BURGER TIME GAME INFO\n";

	std::cout << '\n';

	std::cout << "PLAYER CONTROLS - XBOX CONTROLLER:\n";
	std::cout << "Movement: DPAD left-right-up-down\n";
	std::cout << "Health Decrease: A\n";
	std::cout << "Score Increase: X\n";

	std::cout << '\n';

	std::cout << "PLAYER CONTROLS - KEYBOARD:\n";
	std::cout << "PLAYER 1:\n";
	std::cout << "Movement: W(up), A(left), S(down), D(right)\n";
	std::cout << "Health Decrease: J\n";
	std::cout << "Score Increase: K\n";
	std::cout << "PLAYER 2:\n";
	std::cout << "Movement: ARROW KEYS\n";
	std::cout << "Health Decrease: L\n";
	std::cout << "Score Increase: M\n";

	std::cout << '\n';

	std::cout << "Losing Health will add a sound to the queue\nGaining Score will play a sound over other other sounds\n";
	std::cout << "\nADDITIONAL INFO: Once you reach 0 lives, gaining score or losing health will not be possible anymore,\nso no sounds will play either\n";
}

void BurgerTime::AddPlayer(Scene& scene, const glm::vec3& pos, float scale) const
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
	pp->AddComponent<ControllerComponent>(glm::vec2{ 150.f, 100.f });
	auto ppComp = pp->GetComponent<PeterPepperComponent>();

	pp->GetTransform().SetPosition(pos);
	pp->GetTransform().SetScale(scale);
	scene.Add(pp);

	// Health display
	auto hd = std::make_shared<GameObject>();
	auto hdComp = hd->AddComponent<HealthDisplayComponent>(ppComp);
	ppComp->AddObserver(hdComp);

	hd->GetTransform().SetScale(4.f);
	scene.Add(hd);

	auto sd = std::make_shared<GameObject>();
	auto txtComp = sd->AddComponent<TextComponent>(ResourceManager::GetInstance().LoadFont("origa___.ttf", 30));
	sd->AddComponent<RenderComponent>();
	auto sdComp = sd->AddComponent<ScoreDisplayComponent>(ppComp, txtComp);
	ppComp->AddObserver(sdComp);

	scene.Add(sd);

	InputManager::GetInstance().AddCommand<KillCommand>(ppComp->GetGameObject().lock(), SDLK_j, InputState::down);
	InputManager::GetInstance().AddCommand<ScoreCommand>(ppComp->GetGameObject().lock(), SDLK_k, InputState::down);
	InputManager::GetInstance().AddCommand<MoveLeftCommand>(ppComp->GetGameObject().lock(), SDLK_a);
	InputManager::GetInstance().AddCommand<MoveRightCommand>(ppComp->GetGameObject().lock(), SDLK_d);
	InputManager::GetInstance().AddCommand<MoveUpCommand>(ppComp->GetGameObject().lock(), SDLK_w);
	InputManager::GetInstance().AddCommand<MoveDownCommand>(ppComp->GetGameObject().lock(), SDLK_s);
}