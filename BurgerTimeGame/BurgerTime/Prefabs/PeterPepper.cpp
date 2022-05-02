#include "pch.h"
#include "PeterPepper.h"
#include "Components/PeterPepperComponent.h"
#include "Components/HealthDisplayComponent.h"
#include "Components/ScoreDisplayComponent.h"
#include "Implementations/Command/PlayerCommands.h"

#define GRID_SIZE 16
#define GAME_SCALE 3

uint8_t PeterPepper::m_PlayerID = 0;
std::vector<glm::vec3> PeterPepper::m_PlayerHUDPositions = { {0,440,0}, {550, 440, 0} };

void PeterPepper::Initialize()
{
	if (m_PlayerID > 3) throw std::runtime_error("There can't be more than 4 players in the game");

	auto font	= ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto hudPos = m_PlayerHUDPositions[m_PlayerID];

	// Variables for sprite
	SDL_Rect source{};
	source.x = GRID_SIZE * 3;
	source.y = 0;
	source.w = GRID_SIZE * 3;
	source.h = GRID_SIZE;

	const int width = GRID_SIZE * GAME_SCALE;
	const int height = GRID_SIZE * GAME_SCALE;

	// PeterPepper object
	auto child		=	AddChild(std::make_shared<GameObject>());
	auto ppComp		=	child->AddComponent<PeterPepperComponent>();
	auto renderComp =	child->AddComponent<RenderComponent>();
	child->AddComponent<SpriteComponent>("BurgerTimeSprite.png", 3, 1, 1.f / 10.f, source, width, height);

	// temporary hardcoded player locations
	switch (m_PlayerID)
	{
	case 0:
		child->SetPosition({ 200, 200, 0 });
		break;
	case 1:
		child->SetPosition({ 300, 200, 0 });
		break;
	}

	// HealthDisplay object
	child			=	AddChild(std::make_shared<GameObject>());
	auto txtComp	=	child->AddComponent<TextComponent>();
	renderComp		=	child->AddComponent<RenderComponent>();
	auto hdComp		=	child->AddComponent<HealthDisplayComponent>(ppComp, txtComp);
	txtComp->SetFont(font);

	child->SetPosition(hudPos);

	// ScoreDisplay object
	child			=	AddChild(std::make_shared<GameObject>());
	txtComp			=	child->AddComponent<TextComponent>();
	renderComp		=	child->AddComponent<RenderComponent>();
	auto sdComp		=	child->AddComponent<ScoreDisplayComponent>(ppComp, txtComp);
	txtComp->SetFont(font);

	hudPos.y += 20;
	child->SetPosition(hudPos);

	ppComp->AddObserver(hdComp);
	ppComp->AddObserver(sdComp);

	// Controller input
	InputManager::GetInstance().AddCommand<MoveLeftCommand>(m_PlayerID, ppComp, ControllerButton::GAMEPAD_DPAD_LEFT);
	InputManager::GetInstance().AddCommand<MoveRightCommand>(m_PlayerID, ppComp, ControllerButton::GAMEPAD_DPAD_RIGHT);
	InputManager::GetInstance().AddCommand<MoveUpCommand>(m_PlayerID, ppComp, ControllerButton::GAMEPAD_DPAD_UP);
	InputManager::GetInstance().AddCommand<MoveDownCommand>(m_PlayerID, ppComp, ControllerButton::GAMEPAD_DPAD_DOWN);

	InputManager::GetInstance().AddCommand<KillCommand>(m_PlayerID, ppComp, ControllerButton::GAMEPAD_BUTTON_SOUTH, InputState::down);
	InputManager::GetInstance().AddCommand<ScoreCommand>(m_PlayerID, ppComp, ControllerButton::GAMEPAD_BUTTON_WEST, InputState::down);

	// Keyboard input (add seperately since it's not attached to an id)
	switch (m_PlayerID)
	{
	case 0:
		InputManager::GetInstance().AddCommand<KillCommand>(ppComp, SDLK_j, InputState::down);
		InputManager::GetInstance().AddCommand<ScoreCommand>(ppComp, SDLK_k, InputState::down);

		InputManager::GetInstance().AddCommand<MoveLeftCommand>(ppComp, SDLK_a);
		InputManager::GetInstance().AddCommand<MoveRightCommand>(ppComp, SDLK_d);
		InputManager::GetInstance().AddCommand<MoveUpCommand>(ppComp, SDLK_w);
		InputManager::GetInstance().AddCommand<MoveDownCommand>(ppComp, SDLK_s);
		break;
	case 1:
		InputManager::GetInstance().AddCommand<KillCommand>(ppComp, SDLK_l, InputState::down);
		InputManager::GetInstance().AddCommand<ScoreCommand>(ppComp, SDLK_m, InputState::down);

		InputManager::GetInstance().AddCommand<MoveLeftCommand>(ppComp, SDLK_LEFT);
		InputManager::GetInstance().AddCommand<MoveRightCommand>(ppComp, SDLK_RIGHT);
		InputManager::GetInstance().AddCommand<MoveUpCommand>(ppComp, SDLK_UP);
		InputManager::GetInstance().AddCommand<MoveDownCommand>(ppComp, SDLK_DOWN);
		break;
	}

	++m_PlayerID;
}