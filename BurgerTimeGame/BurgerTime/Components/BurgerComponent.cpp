#include "pch.h"
#include "BurgerComponent.h"

BurgerComponent::BurgerComponent(BurgerType type)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture("LevelSprite.png");
	m_pTexture->SetSource({ 8 * 8, 8 * static_cast<int>(type), 8 * 4, 8 });
}

void BurgerComponent::Update()
{
	auto pos = m_pGameObject.lock()->GetTransform().GetPosition();
	auto scale = m_pGameObject.lock()->GetTransform().GetScale();
	Renderer::GetInstance().AppendTexture(m_pTexture.get(), { pos.x, pos.y }, m_pTexture->GetSource(), { 0,0 }, { scale.x, scale.y });
}