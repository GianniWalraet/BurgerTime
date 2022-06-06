#include "pch.h"
#include "VictoryScene.h"
#include "Singletons/GameState.h"

void VictoryScene::Initialize()
{
	auto font = ResourceManager::GetInstance().LoadFont("origa___.ttf", 70);
	auto textGO = Add(std::make_shared<GameObject>());
	textGO->AddComponent<TextComponent>(font, "VICTORY!", glm::vec2{ 0.5f, 0.5f });
	textGO->AddComponent<RenderComponent>();
	textGO->GetTransform().SetPosition(Renderer::GetInstance().GetWindowWidth() / 2.f, Renderer::GetInstance().GetWindowHeight() / 2.f, 0.f);

	textGO = Add(std::make_shared<GameObject>());
	m_pHighScoreTxt = textGO->AddComponent<TextComponent>(font, "HIGH SCORE: 0", glm::vec2{ 0.5f, 0.5f });
	textGO->AddComponent<RenderComponent>();
	textGO->GetTransform().SetPosition(Renderer::GetInstance().GetWindowWidth() / 2.f, Renderer::GetInstance().GetWindowHeight() / 4.f * 3.f, 0.f);
}

void VictoryScene::OnSceneActivated()
{
	auto& gameState = GameState::GetInstance();
	if (gameState.GetGameMode() == GameMode::SOLO)
	{
		m_pHighScoreTxt.lock()->SetText("SCORE:\n " + std::to_string(std::max(gameState.GetScoreP1(), gameState.GetScoreP2())));
	}
	else
	{
		m_pHighScoreTxt.lock()->SetText("HIGHEST SCORE:\n " + std::to_string(std::max(gameState.GetScoreP1(), gameState.GetScoreP2())));
	}
}
