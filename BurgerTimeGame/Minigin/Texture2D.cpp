#include "MiniginPCH.h"
#include "Texture2D.h"

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
	int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	m_Width = static_cast<float>(w);
	m_Height = static_cast<float>(h);
}
