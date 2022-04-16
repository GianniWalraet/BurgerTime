#pragma once
#include "BaseComponent.h"


class Texture2D;

class TextureComponent : public BaseComponent
{
public:
	TextureComponent(const std::shared_ptr<GameObject>& pOwner) : BaseComponent::BaseComponent(pOwner) {}
	TextureComponent(const std::shared_ptr<GameObject>& pOwner, const std::string& filename, const SDL_Rect& srcRect = { 0,0,0,0 }, int w = 0.f, int h = 0.f);
	virtual ~TextureComponent() = default;
	TextureComponent(const TextureComponent& other) = delete;
	TextureComponent(TextureComponent&& other) = delete;
	TextureComponent& operator=(const TextureComponent& other) = delete;
	TextureComponent& operator=(TextureComponent&& other) = delete;

	const std::shared_ptr<Texture2D>& GetTexture() const { return m_pTexture; };

	const bool HasCustomSource() const { return m_HasCustomSource; }
	const bool HasCustomSize() const { return m_HasCustomSize; }

	const SDL_Rect& GetSrcRect() const { return m_SrcRect; }
	const int GetWidth() const { return m_Width; }
	const int GetHeight() const { return m_Height; }
protected:
	std::shared_ptr<Texture2D> m_pTexture;
	int m_Width{};
	int m_Height{};
private:
	SDL_Rect m_SrcRect{};
	bool m_HasCustomSource{};
	bool m_HasCustomSize{};
};


