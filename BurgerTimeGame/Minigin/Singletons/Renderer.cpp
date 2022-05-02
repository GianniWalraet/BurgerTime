#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneGraph/SceneManager.h"
#include "Graphics/Texture2D.h"
#include <SDL_image.h>

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	SDL_RenderPresent(m_Renderer);
}

void Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void Renderer::RenderTexture(const Texture2D& texture, const int x, const int y, bool mirror) const
{
	SDL_RendererFlip flip = mirror ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE;

	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);

	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, 0.f, nullptr, flip);
}

void Renderer::RenderTexture(const Texture2D& texture, const int x, const int y, const int width, const int height, bool mirror) const
{
	SDL_RendererFlip flip = mirror ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE;

	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, 0.f, nullptr, flip);
}

void Renderer::RenderTexture(const Texture2D& texture, const int x, const int y, const SDL_Rect& srcRect, bool mirror) const
{
	SDL_RendererFlip flip = mirror ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE;

	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);

	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dst, 0.f, nullptr, flip);
}

void Renderer::RenderTexture(const Texture2D& texture, const int x, const int y, const int width, const int height, const SDL_Rect& srcRect, bool mirror) const
{
	SDL_RendererFlip flip = mirror ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE;

	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dst, 0.f, nullptr, flip);
}

const int Renderer::GetWindowWidth() const
{
	int w, h;
	SDL_GetWindowSize(m_Window, &w, &h);
	return w;
}

const int Renderer::GetWindowHeight() const
{
	int w, h;
	SDL_GetWindowSize(m_Window, &w, &h);
	return h;
}
