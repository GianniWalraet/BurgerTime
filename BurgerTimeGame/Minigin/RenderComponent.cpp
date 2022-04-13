#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "TextureComponent.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "GameObject.h"

void RenderComponent::Render()
{
	auto& renderer = Renderer::GetInstance();
	for (const auto& t : m_pTextures)
	{
		auto& pos = m_pOwner.lock()->GetPosition();
		auto& texture = *t->GetTexture().get();
		
		bool customSource = t->HasCustomSource();
		bool customSize = t->HasCustomSize();

		if (customSource && customSize)
		{
			renderer.RenderTexture(texture, pos.x, pos.y, t->GetWidth(), t->GetHeight(), t->GetSrcRect());
			continue;
		}

		if (customSource && !customSize)
		{
			renderer.RenderTexture(texture, pos.x, pos.y, t->GetSrcRect());
			continue;
		}

		if (!customSource && customSize)
		{
			renderer.RenderTexture(texture, pos.x, pos.y, t->GetWidth(), t->GetHeight());
			continue;
		}

		renderer.RenderTexture(texture, pos.x, pos.y);
	}

	for (const auto& p : m_pSprites)
	{
		auto& pos = m_pOwner.lock()->GetPosition();
		renderer.RenderTexture(*p->GetTexture().get(), pos.x, pos.y, p->GetDstWidth(), p->GetDstHeight(), p->GetFrameSrc());
	}
}

void RenderComponent::AddTexture(TextureComponent* tex)
{
	m_pTextures.push_back(tex);
}

void RenderComponent::AddSprite(SpriteComponent* sprite)
{
	m_pSprites.push_back(sprite);
}
