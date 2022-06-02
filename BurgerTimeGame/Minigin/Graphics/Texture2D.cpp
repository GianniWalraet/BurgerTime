#include "MiniginPCH.h"
#include "Texture2D.h"

Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &m_Width, &m_Height);
	m_Source.w = m_Width;
	m_Source.h = m_Height;
}

void Texture2D::SetSource(const SDL_Rect& newSrc)
{
	m_Source = newSrc;
}