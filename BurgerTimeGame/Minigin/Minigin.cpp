#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include <chrono>

#include "Base/Timer.h"
#include "Input/InputManager.h"
#include "SceneGraph/SceneManager.h"
#include "Singletons/Renderer.h"
#include "Singletons/ResourceManager.h"
#include "Sound/ServiceLocator.h"
#include "Sound/SoundManager.h"

using namespace std;

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

void Minigin::InitEngine()
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
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

void Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Minigin::Run()
{
	InitEngine();

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

		// Init objects
		sceneManager.Initialize();

		// Start timer
		timer.Start();

		bool doContinue = true;
		while (doContinue)
		{
			timer.Update();
			const auto currentTime = std::chrono::high_resolution_clock::now();

			doContinue = input.ProcessInput();
			sceneManager.Update();
			renderer.Render();

			const auto sleepTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime + std::chrono::milliseconds(MsPerFrame) - std::chrono::high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	// Stop timer
	timer.Stop();

	Cleanup();
}
