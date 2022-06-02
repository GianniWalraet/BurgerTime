#include "pch.h"
#include "BurgerTime.h"

// Command includes
#include "Implementations/Command/PlayerCommands.h"

// Prefab includes
#include "Prefabs/PeterPepper.h"
#include "Prefabs/Level.h"

void BurgerTime::LoadGame() const
{
#ifdef _DEBUG
	ServiceLocator::RegisterSoundManager(std::make_shared<SoundManager>());
	ServiceLocator::RegisterSoundManager(std::make_shared<LoggedSoundManager>(ServiceLocator::GetSoundManager()));
#else
	ServiceLocator::RegisterSoundManager(std::make_shared<SoundManager>());
	
#endif

	PrintGameInfo();

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	scene.Add(std::make_shared<Level>("../Data/Levels/Level01.txt"));

	// DAE logo
	//auto child = std::make_shared<GameObject>();
	//child->AddComponent<TextureComponent>("logo.png");
	//child->AddComponent<RenderComponent>();
	//child->GetTransform()->SetPosition({ Renderer::GetInstance().GetWindowWidth() / 2.f, Renderer::GetInstance().GetWindowHeight() / 2.f, 0.f });
	//go->AddChild(child);

	// FPS
	auto child = std::make_shared<GameObject>();
	child->AddComponent<TextComponent>(ResourceManager::GetInstance().LoadFont("Lingua.otf", 12));
	child->AddComponent<RenderComponent>();
	child->AddComponent<FPSComponent>();
	scene.Add(child);


	// Players
	auto pp = std::make_shared<PeterPepper>();
	scene.Add(pp);
	//auto pp2 = go->AddChild(std::make_shared<PeterPepper>());

	ServiceLocator::GetSoundManager()->PlayStream("Sounds/Start.mp3", 20, false);
	ServiceLocator::GetSoundManager()->PlayStream("Sounds/MainTheme.mp3", 20, true);
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