#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Singletons/Renderer.h"
#include "Graphics/Texture2D.h"
#include "SceneGraph/GameObject.h"

void RenderComponent::Initialize()
{
	m_pTexture = m_pOwner.lock()->GetComponent<TextureComponent>();
	m_pSprite =  m_pOwner.lock()->GetComponent<SpriteComponent>();
	m_pText = m_pOwner.lock()->GetComponent<TextComponent>();
}

void RenderComponent::Render()
{
	auto& renderer = Renderer::GetInstance();
	if(m_pTexture)
	{
		const Texture2D& texture = *m_pTexture->GetTexture().get();
		const glm::vec3& pos = m_pOwner.lock()->GetTransform()->GetPosition();
		const glm::vec2& scale = m_pOwner.lock()->GetTransform()->GetScale();

		renderer.RenderTexture(texture, { pos.x, pos.y }, texture.GetSource(), scale, m_pTexture->IsMirrored());
	}

	if(m_pSprite)
	{
		const glm::vec3& pos = m_pOwner.lock()->GetTransform()->GetPosition();
		const glm::vec2& scale = m_pOwner.lock()->GetTransform()->GetScale();

		renderer.RenderTexture(*m_pSprite->GetTexture().get(), { pos.x, pos.y }, m_pSprite->GetCurrentFrame(), scale, m_pSprite->IsMirrored());
	}

	if (m_pText)
	{
		const Texture2D& texture = *m_pText->GetTexture().get();
		const glm::vec3& pos = m_pOwner.lock()->GetTransform()->GetPosition();
		const glm::vec2& scale = m_pOwner.lock()->GetTransform()->GetScale();

		renderer.RenderTexture(texture, { pos.x, pos.y }, texture.GetSource(), scale);
	}
}
