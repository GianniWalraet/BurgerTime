#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Singletons/Renderer.h"
#include "Graphics/Texture2D.h"
#include "SceneGraph/GameObject.h"
#include "TextureComponent.h"
#include "SpriteComponent.h"

void RenderComponent::Initialize()
{
	auto texComp = m_pOwner.lock()->GetComponent<TextureComponent>();
	auto spriteComp = m_pOwner.lock()->GetComponent<SpriteComponent>();

	if (texComp) m_pTexture = texComp;
	if (spriteComp) m_pSprite = spriteComp;
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
}
