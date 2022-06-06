#include "pch.h"
#include "HealthDisplayComponent.h"
#include "PeterPepperComponent.h"

HealthDisplayComponent::HealthDisplayComponent(const std::weak_ptr<PeterPepperComponent>& pPlayerC, const glm::vec2& pivot)
	: m_pPlayer{pPlayerC}
	, m_Pivot{pivot}
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture("BurgerTimeSprite.png");
	m_pTexture->SetSource({ 8 * 25,0,8,8 });

	assert(!m_pPlayer.expired());
}

void HealthDisplayComponent::Update()
{
	if (m_pPlayer.expired()) return;

	auto& renderer = Renderer::GetInstance();
	auto pos = m_pGameObject.lock()->GetTransform().GetPosition();
	const auto& scale = m_pGameObject.lock()->GetTransform().GetScale();
	for (size_t i = 0; i < m_pPlayer.lock()->GetLives(); ++i)
	{
		renderer.AppendTexture(m_pTexture.get(), pos, m_pTexture->GetSource(), m_Pivot, scale);
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
