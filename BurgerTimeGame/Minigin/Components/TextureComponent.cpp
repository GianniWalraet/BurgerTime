#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "Graphics/Texture2D.h"
#include "Singletons/ResourceManager.h"
#include "Singletons/Renderer.h"
#include "TransformComponent.h"

TextureComponent::TextureComponent(const std::shared_ptr<GameObject>& pOwner, const std::string& filename, const SDL_Rect& srcRect, int w, int h)
	: BaseComponent::BaseComponent(pOwner)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
	m_SrcRect = srcRect;
	m_Width = w;
	m_Height = h;

	const float epsilon{ 0.001f };
	m_HasCustomSource = (!(srcRect.w > 0 && srcRect.h > 0)) ? false : true;
	m_HasCustomSize = (!(w > epsilon && h > epsilon)) ? false : true;
}
