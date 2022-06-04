#include "pch.h"
#include "HealthDisplayComponent.h"
#include "PeterPepperComponent.h"

HealthDisplayComponent::HealthDisplayComponent(PeterPepperComponent* pPlayerC)
{
	m_pPlayer = pPlayerC;
	m_pTexture = ResourceManager::GetInstance().LoadTexture("BurgerTimeSprite.png");
	m_pTexture->SetSource({ 8 * 25,0,8,8 });

	assert(m_pPlayer != nullptr);
}

void HealthDisplayComponent::Update()
{
	auto& renderer = Renderer::GetInstance();
	glm::vec2 pos{ 0.f, renderer.GetWindowHeight() }, pivot{ -0.1f, 1.1f }, scale{ m_pGameObject.lock()->GetTransform().GetScale() };
	for (size_t i = 0; i < m_pPlayer->GetLives(); ++i)
	{
		renderer.AppendTexture(m_pTexture.get(), pos, m_pTexture->GetSource(), pivot, scale);
		pos.y -= m_pTexture->GetSource().h * scale.y;
	}
}

void HealthDisplayComponent::OnNotify(Event event)
{
	switch (event)
	{
	case Event::PlayerDied:
		//UpdateText();
		break;
	}
}
