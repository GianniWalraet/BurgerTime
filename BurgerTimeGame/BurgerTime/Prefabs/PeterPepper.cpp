#include "pch.h"
#include "PeterPepper.h"
#include "Components/PeterPepperComponent.h"
#include "Components/HealthDisplayComponent.h"
#include "Components/ScoreDisplayComponent.h"
#include "Command/PlayerCommands.h"

uint8_t PeterPepper::m_PlayerID = 0;
uint8_t PeterPepper::m_MaxPlayers = 4;

void PeterPepper::Initialize()
{
	if (m_PlayerID > (m_MaxPlayers - 1)) throw std::runtime_error("There can't be more than 4 players in the game");

	auto font	= ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);

	// Variables for sprite
	int gridBoxSize{ 16 };
	SDL_Rect source{};
	source.x = gridBoxSize * 3;
	source.y = 0;
	source.w = gridBoxSize * 3;
	source.h = gridBoxSize;

	// PeterPepper object
	AddComponent<PeterPepperComponent>();
	AddComponent<RenderComponent>();
	AddComponent<SpriteComponent>("BurgerTimeSprite.png", 3, 1, 1.f / 10.f, glm::vec2{ 0.5f, 1.f }, source);
	AddComponent<ControllerComponent>(150.f);

	//HealthDisplay object
	//child = AddChild(std::make_shared<GameObject>());
	//auto txtComp = child->AddComponent<TextComponent>(font);
	//child->AddComponent<RenderComponent>();
	//auto hdComp	= child->AddComponent<HealthDisplayComponent>(ppComp, txtComp);

	// ScoreDisplay object
	//child =	AddChild(std::make_shared<GameObject>());
	//txtComp = child->AddComponent<TextComponent>(font);
	//child->AddComponent<RenderComponent>();
	//auto sdComp	= child->AddComponent<ScoreDisplayComponent>(ppComp, txtComp);

	//ppComp->AddObserver(hdComp);
	//ppComp->AddObserver(sdComp);

	// Controller input
	InputManager::GetInstance().AddCommand<MoveLeftCommand>(m_PlayerID, shared_from_this(), ControllerButton::GAMEPAD_DPAD_LEFT);
	InputManager::GetInstance().AddCommand<MoveRightCommand>(m_PlayerID, shared_from_this(), ControllerButton::GAMEPAD_DPAD_RIGHT);
	InputManager::GetInstance().AddCommand<MoveUpCommand>(m_PlayerID, shared_from_this(), ControllerButton::GAMEPAD_DPAD_UP);
	InputManager::GetInstance().AddCommand<MoveDownCommand>(m_PlayerID, shared_from_this(), ControllerButton::GAMEPAD_DPAD_DOWN);

	InputManager::GetInstance().AddCommand<KillCommand>(m_PlayerID, shared_from_this(), ControllerButton::GAMEPAD_BUTTON_SOUTH, InputState::down);
	InputManager::GetInstance().AddCommand<ScoreCommand>(m_PlayerID, shared_from_this(), ControllerButton::GAMEPAD_BUTTON_WEST, InputState::down);

	// Keyboard input (add seperately since it's not attached to an id)
	switch (m_PlayerID)
	{
	case 0:
		InputManager::GetInstance().AddCommand<KillCommand>(shared_from_this(), SDLK_j, InputState::down);
		InputManager::GetInstance().AddCommand<ScoreCommand>(shared_from_this(), SDLK_k, InputState::down);

		InputManager::GetInstance().AddCommand<MoveLeftCommand>(shared_from_this(), SDLK_a);
		InputManager::GetInstance().AddCommand<MoveRightCommand>(shared_from_this(), SDLK_d);
		InputManager::GetInstance().AddCommand<MoveUpCommand>(shared_from_this(), SDLK_w);
		InputManager::GetInstance().AddCommand<MoveDownCommand>(shared_from_this(), SDLK_s);
		break;
	case 1:
		InputManager::GetInstance().AddCommand<KillCommand>(shared_from_this(), SDLK_l, InputState::down);
		InputManager::GetInstance().AddCommand<ScoreCommand>(shared_from_this(), SDLK_m, InputState::down);

		InputManager::GetInstance().AddCommand<MoveLeftCommand>(shared_from_this(), SDLK_LEFT);
		InputManager::GetInstance().AddCommand<MoveRightCommand>(shared_from_this(), SDLK_RIGHT);
		InputManager::GetInstance().AddCommand<MoveUpCommand>(shared_from_this(), SDLK_UP);
		InputManager::GetInstance().AddCommand<MoveDownCommand>(shared_from_this(), SDLK_DOWN);
		break;
	}

	++m_PlayerID;
}