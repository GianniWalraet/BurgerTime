#include "pch.h"
#include "DefeatScene.h"

void DefeatScene::Initialize()
{
	auto font = ResourceManager::GetInstance().LoadFont("origa___.ttf", 70);
	auto textGO = Add(std::make_shared<GameObject>());
	textGO->AddComponent<TextComponent>(font, "GAME OVER", glm::vec2{ 0.5f, 0.5f });
	textGO->AddComponent<RenderComponent>();
	textGO->GetTransform().SetPosition(Renderer::GetInstance().GetWindowWidth() / 2.f, Renderer::GetInstance().GetWindowHeight() / 2.f, 0.f);
}