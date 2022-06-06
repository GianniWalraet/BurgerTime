#include "pch.h"
#include "MainMenuScene.h"
#include "Singletons/GameState.h"

void MainMenuScene::Initialize()
{
	auto font = ResourceManager::GetInstance().LoadFont("origa___.ttf", 70);
	auto windowW = Renderer::GetInstance().GetWindowWidth();
	auto windowH = Renderer::GetInstance().GetWindowHeight();

	auto txtGO = Add(std::make_shared<GameObject>());
	txtGO->AddComponent<TextComponent>(font, "BURGER TIME", glm::vec2{0.5f, 0.5f});
	txtGO->AddComponent<RenderComponent>();
	txtGO->GetTransform().SetPosition({ windowW / 2.f, windowH / 10.f, 0.f });



	font = ResourceManager::GetInstance().LoadFont("origa___.ttf", 40);

	txtGO = Add(std::make_shared<GameObject>());
	txtGO->AddComponent<TextComponent>(font, "SINGLEPLAYER: PRESS S", glm::vec2{ 0.5f, 0.5f });
	txtGO->AddComponent<RenderComponent>();
	txtGO->GetTransform().SetPosition({ windowW / 2.f, windowH / 5.f * 2.f, 0.f });

	txtGO = Add(std::make_shared<GameObject>());
	txtGO->AddComponent<TextComponent>(font, "MULTIPLAYER: PRESS M", glm::vec2{ 0.5f, 0.5f });
	txtGO->AddComponent<RenderComponent>();
	txtGO->GetTransform().SetPosition({ windowW / 2.f, windowH / 5.f * 3.f , 0.f });
}
void MainMenuScene::Update()
{
	if(InputManager::GetInstance().WentDownThisFrame(SDLK_s))
	{
		GameState::GetInstance().OnReset(GameMode::SINGLEPLAYER);
		SceneManager::GetInstance().SetActiveScene("Level01Scene");
	}
	else if (InputManager::GetInstance().WentDownThisFrame(SDLK_m))
	{
		GameState::GetInstance().OnReset(GameMode::MULTIPLAYER);
		SceneManager::GetInstance().SetActiveScene("Level01Scene");
	}
}

void MainMenuScene::OnSceneActivated()
{
	ServiceLocator::GetSoundManager()->PlayStream("Sounds/MainMenuTheme.mp3", GameData::SoundtrackVolume, true);
}
void MainMenuScene::OnSceneDeactivated()
{
	ServiceLocator::GetSoundManager()->StopStream();
}