#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"

TextureComponent::TextureComponent(const std::string& filename, const glm::vec4& srcRect, float w, float h)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
	m_SrcRect = srcRect;
	m_Width = w;
	m_Height = h;

	const float epsilon{ 0.001f };
	m_HasCustomSource = (!(srcRect.z > epsilon && srcRect.w > epsilon)) ? false : true;
	m_HasCustomSize = (!(w > epsilon && h > epsilon)) ? false : true;
}
