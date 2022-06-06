#include "pch.h"
#include "Helpers.h"
#include "Components/MrHotDogComponent.h"

std::shared_ptr<GameObject> Helpers::AddPlayer(const std::shared_ptr<Scene>& scene, PlayerID id)
{
	if (static_cast<int>(id) < 0) throw std::runtime_error("invalid player id");
	if(static_cast<int>(id) > GameData::MaxPlayers) throw std::runtime_error("error: max 2 players allowed");

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);

	SDL_Rect source{};
	source.x = GameData::SpriteCellSize * 3;
	source.y = 0;
	source.w = GameData::SpriteCellSize * 3;
	source.h = GameData::SpriteCellSize;

	// Peter Pepper
	auto pp = std::make_shared<GameObject>();
	pp->AddComponent<PeterPepperComponent>();
	pp->AddComponent<SpriteComponent>("BurgerTimeSprite.png", 3, 1, 1.f / 15.f, glm::vec2{ 0.5f, 1.f }, source);
	pp->AddComponent<RenderComponent>();
	pp->AddComponent<Box2DComponent>(float(GameData::SpriteCellSize), float(GameData::SpriteCellSize), true);
	pp->AddComponent<ControllerComponent>(glm::vec2{ 150.f, 100.f });
	auto ppComp = pp->GetComponent<PeterPepperComponent>();

	scene->Add(pp);

	// Health display
	auto hd = std::make_shared<GameObject>();
	glm::vec2 pivot{};
	switch (id)
	{
	case PlayerID::PLAYERONE:
		hd->GetTransform().SetPosition(0.f, float(Renderer::GetInstance().GetWindowHeight()), 0.f);
		pivot = { -0.1f, 1.1f };
		break;
	case PlayerID::PLAYERTWO:
		hd->GetTransform().SetPosition(float(Renderer::GetInstance().GetWindowWidth()), float(Renderer::GetInstance().GetWindowHeight()), 0.f);
		pivot = { 1.1f, 1.1f };
		break;
	}

	auto hdComp = hd->AddComponent<HealthDisplayComponent>(ppComp, pivot);
	ppComp->AddObserver(hdComp);

	hd->GetTransform().SetScale(4.f);
	scene->Add(hd);

	auto sd = std::make_shared<GameObject>();

	pivot = { 0.f, 0.f };
	if (id == PlayerID::PLAYERTWO)
	{
		sd->GetTransform().SetPosition(float(Renderer::GetInstance().GetWindowWidth()), 0.f, 0.f);
		pivot.x = 1.f;
	}

	auto txtComp = sd->AddComponent<TextComponent>(ResourceManager::GetInstance().LoadFont("origa___.ttf", 30), "0", pivot);
	sd->AddComponent<RenderComponent>();
	auto sdComp = sd->AddComponent<ScoreDisplayComponent>(ppComp, txtComp);
	ppComp->AddObserver(sdComp);

	scene->Add(sd);

	auto sceneName = scene->GetName();

	InputManager::GetInstance().AddCommand<MoveLeftCommand>(sceneName, static_cast<int>(id), pp, ControllerButton::GAMEPAD_DPAD_LEFT);
	InputManager::GetInstance().AddCommand<MoveRightCommand>(sceneName, static_cast<int>(id), pp, ControllerButton::GAMEPAD_DPAD_RIGHT);
	InputManager::GetInstance().AddCommand<MoveUpCommand>(sceneName, static_cast<int>(id), pp, ControllerButton::GAMEPAD_DPAD_UP);
	InputManager::GetInstance().AddCommand<MoveDownCommand>(sceneName, static_cast<int>(id), pp, ControllerButton::GAMEPAD_DPAD_DOWN);

	// keyboard commands for debug testing
#ifdef _DEBUG
	InputManager::GetInstance().AddCommand<KillCommand>(sceneName, pp, SDLK_j, InputState::down);
	InputManager::GetInstance().AddCommand<ScoreCommand>(sceneName, pp, SDLK_k, InputState::down);
	InputManager::GetInstance().AddCommand<MoveLeftCommand>(sceneName, pp, SDLK_a);
	InputManager::GetInstance().AddCommand<MoveRightCommand>(sceneName, pp, SDLK_d);
	InputManager::GetInstance().AddCommand<MoveUpCommand>(sceneName, pp, SDLK_w);
	InputManager::GetInstance().AddCommand<MoveDownCommand>(sceneName, pp, SDLK_s);
#endif

	pp->SetTag("Player");
	return pp;
}
std::shared_ptr<GameObject> Helpers::AddMrHotDog(const std::shared_ptr<Scene>& scene)
{
	std::shared_ptr<GameObject> mrHotDog = scene->Add(std::make_shared<GameObject>());
	mrHotDog->AddComponent<SpriteComponent>("BurgerTimeSprite.png", 1, 2, 1 / 10.f, glm::vec2{ 0.5f,1.f }, SDL_Rect{ 0, GameData::SpriteCellSize * 2, GameData::SpriteCellSize * 2, GameData::SpriteCellSize });
	mrHotDog->AddComponent<RenderComponent>();
	mrHotDog->AddComponent<MrHotDogComponent>();
	mrHotDog->AddComponent<Box2DComponent>(float(GameData::SpriteCellSize), float(GameData::SpriteCellSize), true);
	mrHotDog->GetTransform().SetScale(GameData::GameScale);
	mrHotDog->SetTag("Enemy");

	return mrHotDog;
}
