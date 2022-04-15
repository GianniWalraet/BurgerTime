#include "pch.h"
#include "BurgerTime.h"
#include "PeterPepperComponent.h"
#include "ScoreDisplayComponent.h"
#include "HealthDisplayComponent.h"
#include "PlayerCommands.h"

#define GRID_SIZE 16.f
#define GAME_SCALE 3.f

void BurgerTime::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	// Main gameObject and background
	auto go = std::make_shared<GameObject>();
	auto texComp = go->AddComponent<TextureComponent>("background.jpg");
	auto renderComp = go->AddComponent<RenderComponent>();
	//renderComp->AddTexture(texComp);

	// dae logo
	auto child = std::make_shared<GameObject>();
	texComp = child->AddComponent<TextureComponent>("logo.png");
	renderComp = child->AddComponent<RenderComponent>();
	//renderComp->AddTexture(texComp);
	child->SetPosition({ 216, 50, 0 });
	go->AddChild(child);

	// Text
	//child = std::make_shared<GameObject>();
	//auto txtComp = child->AddComponent<TextComponent>();
	//renderComp = child->AddComponent<RenderComponent>();
	//txtComp->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
	//txtComp->SetText("Programming 4 Assignment");
	//renderComp->AddTexture(txtComp);
	//child->SetPosition({ 80, 20, 0 });
	//go->AddChild(child);

	// FPS
	child = std::make_shared<GameObject>();
	auto fpsComp = child->AddComponent<FPSComponent>();
	auto txtComp = child->AddComponent<TextComponent>();
	renderComp = child->AddComponent<RenderComponent>();
	txtComp->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
	txtComp->SetText("0");
	//renderComp->AddTexture(txtComp);
	go->AddChild(child);

	// Players
	auto p1 = AddPlayer(go.get(), 0, { 200,200,0 }, { 0,430,0 }, { 0,450,0 });
	auto p2 = AddPlayer(go.get(), 1, { 300,200,0 }, { 550,430,0 }, { 550,450,0 });
	InputManager::GetInstance().AddCommand<KillCommand>(p1, SDLK_j);
	InputManager::GetInstance().AddCommand<ScoreCommand>(p1, SDLK_k);
	InputManager::GetInstance().AddCommand<KillCommand>(p2, SDLK_l);
	InputManager::GetInstance().AddCommand<ScoreCommand>(p2, SDLK_m);
	InputManager::GetInstance().AddCommand<MoveLeftCommand>(p1, SDLK_a);
	InputManager::GetInstance().AddCommand<MoveRightCommand>(p1, SDLK_d);
	InputManager::GetInstance().AddCommand<MoveUpCommand>(p1, SDLK_w);
	InputManager::GetInstance().AddCommand<MoveDownCommand>(p1, SDLK_s);

	scene.Add(go);

	std::cout << "Player dead: Press BUTTON_SOUTH\n";
	std::cout << "Player Gain Score: Press BUTTON WEST\n";
	std::cout << "Player Win: Reach 500 score\n";
}

PeterPepperComponent* BurgerTime::AddPlayer(GameObject* parent, uint32_t playerId, const glm::vec3& playerPos, const glm::vec3& healthDisplayPos, const glm::vec3& scoreDisplayPos) const
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);

	auto child = std::make_shared<GameObject>();
	auto ppComp = child->AddComponent<PeterPepperComponent>();
	glm::vec4 srcRect = { 0,0,GRID_SIZE,GRID_SIZE };
	//auto texComp = child->AddComponent<TextureComponent>(new TextureComponent("BurgerTimeSprite.png", srcRect, GRID_SIZE * GAME_SCALE, GRID_SIZE * GAME_SCALE));
	auto sprComp = child->AddComponent<SpriteComponent>("BurgerTimeSprite.png", 3, 1, 1.f / 10.f,
	glm::vec4{ GRID_SIZE * 3.f, 0.f, GRID_SIZE * 3.f, GRID_SIZE }, GRID_SIZE * GAME_SCALE, GRID_SIZE * GAME_SCALE);
	auto renderComp = child->AddComponent<RenderComponent>();
	//renderComp->AddSprite(sprComp);
	//renderComp->AddTexture(texComp);
	child->SetPosition(playerPos);
	parent->AddChild(child);

	child = std::make_shared<GameObject>();
	auto txtComp = child->AddComponent<TextComponent>();
	renderComp = child->AddComponent<RenderComponent>();
	auto hdComp = child->AddComponent<HealthDisplayComponent>(ppComp, txtComp);

	txtComp->SetFont(font);
	//renderComp->AddTexture(txtComp);
	child->SetPosition(healthDisplayPos);
	parent->AddChild(child);

	child =			std::make_shared<GameObject>();
	txtComp =		child->AddComponent<TextComponent>();
	renderComp =	child->AddComponent<RenderComponent>();
	auto sdComp = child->AddComponent<ScoreDisplayComponent>(ppComp, txtComp);

	ppComp->AddObserver(hdComp);
	ppComp->AddObserver(sdComp);

	txtComp->SetFont(font);
	//renderComp->AddTexture(txtComp);
	child->SetPosition(scoreDisplayPos);
	parent->AddChild(child);

	InputManager::GetInstance().AddCommand<KillCommand>(playerId, ppComp, ControllerButton::GAMEPAD_BUTTON_SOUTH);
	InputManager::GetInstance().AddCommand<ScoreCommand>(playerId, ppComp, ControllerButton::GAMEPAD_BUTTON_WEST);
	return ppComp;
}