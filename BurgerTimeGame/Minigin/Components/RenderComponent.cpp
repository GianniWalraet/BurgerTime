#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Singletons/Renderer.h"
#include "Graphics/Texture2D.h"
#include "SceneGraph/GameObject.h"

void RenderComponent::Initialize()
{
	m_pTexture = m_pGameObject.lock()->GetComponent<TextureComponent>();
	m_pSprite =  m_pGameObject.lock()->GetComponent<SpriteComponent>();
	m_pText = m_pGameObject.lock()->GetComponent<TextComponent>();
}

void RenderComponent::Render()
{
	auto& renderer = Renderer::GetInstance();
	if(!m_pTexture.expired())
	{
		const Texture2D& texture = *m_pTexture.lock()->GetTexture().get();
		const glm::vec3& pos = m_pGameObject.lock()->GetTransform().GetPosition();
		const glm::vec2& scale = m_pGameObject.lock()->GetTransform().GetScale();

		renderer.RenderTexture(texture, { pos.x, pos.y }, texture.GetSource(), m_pTexture.lock()->GetPivot(), scale, m_pTexture.lock()->IsMirrored());
	}

	if(!m_pSprite.expired())
	{
		const glm::vec3& pos = m_pGameObject.lock()->GetTransform().GetPosition();
		const glm::vec2& scale = m_pGameObject.lock()->GetTransform().GetScale();

		renderer.RenderTexture(*m_pSprite.lock()->GetTexture().get(), {pos.x, pos.y}, m_pSprite.lock()->GetCurrentFrame(), m_pSprite.lock()->GetPivot(), scale, m_pSprite.lock()->IsMirrored());
	}

	if (!m_pText.expired())
	{
		if (auto tex = m_pText.lock()->GetTexture().get(); tex != nullptr)
		{
			const glm::vec3& pos = m_pGameObject.lock()->GetTransform().GetPosition();
			const glm::vec2& scale = m_pGameObject.lock()->GetTransform().GetScale();

			renderer.RenderTexture(*tex, { pos.x, pos.y }, tex->GetSource(), m_pText.lock()->GetPivot(), scale);
		}	
	}
}
