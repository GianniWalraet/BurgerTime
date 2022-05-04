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
		auto& pos = m_pOwner.lock()->GetPosition();
		auto& texture = *m_pTexture->GetTexture().get();
		
		bool customSource = m_pTexture->HasCustomSource();
		bool customSize = m_pTexture->HasCustomSize();

		int x{ static_cast<int>(pos.x) }, y{ static_cast<int>(pos.y) };

		if (customSource && customSize)
		{
			renderer.RenderTexture(texture, x, y, m_pTexture->GetWidth(), m_pTexture->GetHeight(), m_pTexture->GetSrcRect());
		}
		else if (customSource && !customSize)
		{
			renderer.RenderTexture(texture, x, y, m_pTexture->GetSrcRect());
		}
		else if (!customSource && customSize)
		{
			renderer.RenderTexture(texture, x, y, m_pTexture->GetWidth(), m_pTexture->GetHeight());
		}

		renderer.RenderTexture(texture, x, y);
	}

	if(m_pSprite)
	{
		auto& pos = m_pOwner.lock()->GetPosition();
		renderer.RenderTexture(*m_pSprite->GetTexture().get(), static_cast<int>(pos.x), static_cast<int>(pos.y), m_pSprite->GetDstWidth(), m_pSprite->GetDstHeight(), m_pSprite->GetFrameSrc());
	}
}

//void RenderComponent::AddTexture(TextureComponent* tex)
//{
//	m_pTexture.push_back(tex);
//}
//
//void RenderComponent::AddSprite(SpriteComponent* sprite)
//{
//	m_pSprite.push_back(sprite);
//}
