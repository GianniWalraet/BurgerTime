#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include <chrono>
#include "Timer.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"

// Steam
#include <steam_api.h>

// Component includes
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "RenderComponent.h"
#include "PeterPepperComponent.h"
#include "HealthDisplayComponent.h"
#include "ScoreDisplayComponent.h"
#include "SpriteComponent.h"

using namespace std;

#define GRID_SIZE 16
#define GAME_SCALE 5

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	// Main gameObject and background
	auto go = std::make_shared<GameObject>();
	//auto texComp = go->AddComponent<TextureComponent>(new TextureComponent("background.jpg"));
	//auto renderComp = go->AddComponent<RenderComponent>();
	//renderComp->AddTexture(texComp);

	// dae logo
	auto child = std::make_shared<GameObject>();
	//texComp = child->AddComponent<TextureComponent>(new TextureComponent("logo.png"));
	//renderComp = child->AddComponent<RenderComponent>();
	//renderComp->AddTexture(texComp);
	//child->SetPosition({ 216, 180, 0 });
	//go->AddChild(child);

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
	auto renderComp = child->AddComponent<RenderComponent>();
	fpsComp->SetTextComponent(txtComp);
	txtComp->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
	txtComp->SetText("0");
	renderComp->AddTexture(txtComp);
	go->AddChild(child);

	// Player 1
	auto p1 = AddPlayer(go.get(), 0, { 200,200,0 }, { 0,380,0 }, { 0,400,0 });
	auto p2 = AddPlayer(go.get(), 1, { 300,200,0 }, { 0,430,0 }, { 0,450,0 });
	InputManager::GetInstance().AddCommand<KillCommand>(p1, SDLK_a);
	InputManager::GetInstance().AddCommand<ScoreCommand>(p1, SDLK_z);
	InputManager::GetInstance().AddCommand<KillCommand>(p2, SDLK_e);
	InputManager::GetInstance().AddCommand<ScoreCommand>(p2, SDLK_r);

	scene.Add(go);

	std::cout << "Player dead: Press BUTTON_SOUTH\n";
	std::cout << "Player Gain Score: Press BUTTON WEST\n";
	std::cout << "Player Win: Reach 500 score\n";
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	// Init timer
	auto& timer = Timer::GetInstance();
	timer.Initialize();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		// Init input
		input.Initialize();

		// Start timer
		timer.Start();

		bool doContinue = true;
		while (doContinue)
		{
			const auto currentTime = std::chrono::high_resolution_clock::now();
			timer.Update();

			doContinue = input.ProcessInput();
			sceneManager.Update();
			renderer.Render();
			SteamAPI_RunCallbacks();

			const auto sleepTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime + std::chrono::milliseconds(MsPerFrame) - std::chrono::high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	// Stop timer
	timer.Stop();

	Cleanup();
}

dae::PeterPepperComponent* dae::Minigin::AddPlayer(GameObject* parent, UINT playerId, const glm::vec3& playerPos, const glm::vec3& healthDisplayPos, const glm::vec3& scoreDisplayPos) const
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);

	auto child = std::make_shared<GameObject>();
	auto ppComp = child->AddComponent<PeterPepperComponent>();
	glm::vec4 srcRect = { 0,0,GRID_SIZE,GRID_SIZE };
	//auto texComp = child->AddComponent<TextureComponent>(new TextureComponent("BurgerTimeSprite.png", srcRect, GRID_SIZE * GAME_SCALE, GRID_SIZE * GAME_SCALE));
	auto sprComp = child->AddComponent<SpriteComponent>(new SpriteComponent("BurgerTimeSprite.png", 3, 1, 1.f/10.f, 
		glm::vec4{ GRID_SIZE * 3, 0, GRID_SIZE * 3, GRID_SIZE }, GRID_SIZE * GAME_SCALE, GRID_SIZE * GAME_SCALE));
	auto renderComp = child->AddComponent<RenderComponent>();
	renderComp->AddSprite(sprComp);
	//renderComp->AddTexture(texComp);
	child->SetPosition(playerPos);
	parent->AddChild(child);

	child = std::make_shared<GameObject>();
	auto txtComp = child->AddComponent<TextComponent>();
	renderComp = child->AddComponent<RenderComponent>();
	auto hdComp = child->AddComponent<HealthDisplayComponent>(new HealthDisplayComponent(ppComp, txtComp));

	txtComp->SetFont(font);
	renderComp->AddTexture(txtComp);
	child->SetPosition(healthDisplayPos);
	parent->AddChild(child);

	child = std::make_shared<GameObject>();
	txtComp = child->AddComponent<TextComponent>();
	renderComp = child->AddComponent<RenderComponent>();
	auto sdComp = child->AddComponent<ScoreDisplayComponent>(new ScoreDisplayComponent(ppComp, txtComp));

	ppComp->AddObserver(hdComp);
	ppComp->AddObserver(sdComp);

	txtComp->SetFont(font);
	renderComp->AddTexture(txtComp);
	child->SetPosition(scoreDisplayPos);
	parent->AddChild(child);

	InputManager::GetInstance().AddCommand<KillCommand>(playerId, ppComp, ControllerButton::GAMEPAD_BUTTON_SOUTH);
	InputManager::GetInstance().AddCommand<ScoreCommand>(playerId, ppComp, ControllerButton::GAMEPAD_BUTTON_WEST);
	return ppComp;
}
