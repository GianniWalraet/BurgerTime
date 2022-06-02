#pragma once
#include "Base/Singleton.h"


class Texture2D;
/**
 * Simple RAII wrapper for the SDL renderer
 */
class Renderer final : public Singleton<Renderer>
{
public:
	void Init(SDL_Window* window);
	void Render() const;
	void Destroy();

	void RenderTexture(const Texture2D& texture, const glm::vec2& pos, const SDL_Rect& source, const glm::vec2& scale = { 1, 1 }, bool mirror = false) const;

	SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

	const int GetWindowWidth() const;
	const int GetWindowHeight() const;

	const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
	void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
private:
	friend class Singleton<Renderer>;
	SDL_Renderer* m_Renderer{};
	SDL_Window* m_Window{};
	SDL_Color m_clearColor{};
};


