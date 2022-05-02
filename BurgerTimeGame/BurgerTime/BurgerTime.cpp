#include "pch.h"
#include "BurgerTime.h"

// Command includes
#include "Implementations/Command/PlayerCommands.h"

// Prefab includes
#include "Prefabs/PeterPepper.h"

void BurgerTime::LoadGame() const
{
	auto& locator = ServiceLocator::GetInstance();
#ifdef _DEBUG
	locator.RegisterSoundManager(std::make_shared<SoundManager>());
	locator.RegisterSoundManager(std::make_shared<LoggedSoundManager>(locator.GetSoundManager()));
#else
	locator.RegisterSoundManager(std::make_shared<SoundManager>());
#endif

	PrintGameInfo();

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	// Background (everything is attached to this)
	auto go =			std::make_shared<GameObject>();
	auto texComp =		go->AddComponent<TextureComponent>("background.jpg");
	auto renderComp =	go->AddComponent<RenderComponent>();

	// DAE logo
	auto child =		std::make_shared<GameObject>();
	texComp =			child->AddComponent<TextureComponent>("logo.png");
	renderComp =		child->AddComponent<RenderComponent>();
	child->SetPosition({ 216, 50, 0 });
	go->AddChild(child);

	// FPS
	child =				std::make_shared<GameObject>();
	auto txtComp =		child->AddComponent<TextComponent>();
	renderComp =		child->AddComponent<RenderComponent>();
	child->AddComponent<FPSComponent>();
	txtComp->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
	go->AddChild(child);

	// Players
	go->AddChild(std::make_shared<PeterPepper>());
	go->AddChild(std::make_shared<PeterPepper>());

	scene.Add(go);

	ServiceLocator::GetInstance().GetSoundManager()->PlayStream("Sounds/Start.mp3", 20, false);
	ServiceLocator::GetInstance().GetSoundManager()->PlayStream("Sounds/MainTheme.mp3", 20, true);
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