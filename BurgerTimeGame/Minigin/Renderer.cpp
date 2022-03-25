#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "ImGuiManager.h"
#include "Texture2D.h"
#include <SDL_image.h>
#include <gl/GL.h>

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

void dae::Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	ImGuiManager::GetInstance().Initialize(window);
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();
	
	//ImGuiManager::GetInstance().Render();

	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{
	ImGuiManager::GetInstance().Destroy();

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const glm::vec4& srcRect) const
{
	SDL_Rect src{};
	src.x = static_cast<int>(srcRect.x);
	src.y = static_cast<int>(srcRect.y);
	src.w = static_cast<int>(srcRect.z);
	src.h = static_cast<int>(srcRect.w);
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, float x, float y, float width, float height, const glm::vec4& srcRect) const
{
	SDL_Rect src{};
	src.x = static_cast<int>(srcRect.x);
	src.y = static_cast<int>(srcRect.y);
	src.w = static_cast<int>(srcRect.z);
	src.h = static_cast<int>(srcRect.w);
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);

	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);

	// For mirrored drawing

	/*SDL_Rect dst2{};
	dst2.x = -dst.w / 2;
	dst2.y = -dst.h / 2;
	dst2.w = dst.w;
	dst2.h = dst.h;

	glPushMatrix();
	glTranslatef(GLfloat((dst.w / 2) + dst.x), GLfloat((dst.h / 2) + dst.y), 0.f);
	glScalef(-1, 1, 1);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst2);
	glPopMatrix();*/
}
