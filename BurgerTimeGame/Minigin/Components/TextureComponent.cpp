#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "Graphics/Texture2D.h"
#include "Singletons/ResourceManager.h"
#include "Singletons/Renderer.h"
#include "TransformComponent.h"

TextureComponent::TextureComponent(const std::string& filename, bool mirrored, const SDL_Rect& srcRect)
	: m_IsMirrored{ mirrored }
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
	if (srcRect.w != 0 && srcRect.h != 0)
	{
		m_pTexture->SetSource(srcRect);
	}
}