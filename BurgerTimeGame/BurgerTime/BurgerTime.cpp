#include "pch.h"
#include "BurgerTime.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/Level01Scene.h"
#include "Scenes/Level02Scene.h"

void BurgerTime::LoadGame() const
{
#ifdef _DEBUG
	ServiceLocator::RegisterSoundManager(std::make_shared<SoundManager>());
	ServiceLocator::RegisterSoundManager(std::make_shared<LoggedSoundManager>(ServiceLocator::GetSoundManager()));
#else
	ServiceLocator::RegisterSoundManager(std::make_shared<SoundManager>());
#endif
	PrintGameInfo();

	SceneManager::GetInstance().AddScene(std::make_shared<MainMenuScene>());
	SceneManager::GetInstance().AddScene(std::make_shared<Level01Scene>());
	SceneManager::GetInstance().AddScene(std::make_shared<Level02Scene>());
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