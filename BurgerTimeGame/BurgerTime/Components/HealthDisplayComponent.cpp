#include "pch.h"
#include "HealthDisplayComponent.h"
#include "PeterPepperComponent.h"

HealthDisplayComponent::HealthDisplayComponent(PeterPepperComponent* pPlayerC, TextComponent* pTextC)
{
	m_pPlayer = pPlayerC;
	m_pText = pTextC;
	m_pTexture = ResourceManager::GetInstance().LoadTexture("BurgerTimeSprite.png");
	m_pTexture->SetSource({ 0,0,16,16 });

	assert(m_pPlayer != nullptr);
	assert(m_pText != nullptr);

	UpdateText();
}

void HealthDisplayComponent::Update()
{
	auto& renderer = Renderer::GetInstance();
	glm::vec2 pos{ renderer.GetWindowWidth(), 0.f }, pivot{ 1.f, 0.f }, scale{ 1.f, 1.f };
	for (size_t i = 0; i < m_pPlayer->GetLives(); ++i)
	{
		renderer.AppendTexture(m_pTexture.get(), pos, m_pTexture->GetSource(), pivot, scale);
		pos.x -= m_pTexture->GetWidth();
	}
}

void HealthDisplayComponent::Notify(Event event)
{
	switch (event)
	{
	case Event::PlayerDied:
		UpdateText();
		break;
	}
}

void HealthDisplayComponent::UpdateText()
{
	if (!m_pPlayer || !m_pText)
		return;

	m_pText->SetText("Lives: " + std::to_string(m_pPlayer->GetLives()));
}
