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

void Renderer::RenderTexture(const Texture2D& texture, const glm::vec2& pos, const SDL_Rect& source, const glm::vec2& scale, bool mirror) const
{
	SDL_RendererFlip flip = mirror ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE;

	SDL_Rect dst{};
	dst.x = static_cast<int>(pos.x);
	dst.y = static_cast<int>(pos.y);
	dst.w = static_cast<int>(source.w * scale.x);
	dst.h = static_cast<int>(source.h * scale.y);


	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &source, &dst, 0.f, nullptr, flip);
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
