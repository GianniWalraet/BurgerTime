#pragma once
#include "BaseComponent.h"

class Texture2D;

class TextureComponent final : public BaseComponent
{
public:
	TextureComponent(const std::string& filename, const glm::vec2& pivot = {0, 0}, bool mirrored = false, const SDL_Rect& srcRect = {0,0,0,0});
	virtual ~TextureComponent() = default;
	TextureComponent(const TextureComponent& other) = delete;
	TextureComponent(TextureComponent&& other) = delete;
	TextureComponent& operator=(const TextureComponent& other) = delete;
	TextureComponent& operator=(TextureComponent&& other) = delete;

	const std::shared_ptr<Texture2D>& GetTexture() const { return m_pTexture; };
	const glm::vec2& GetPivot() const { return m_Pivot; }

	const bool IsMirrored() const { return m_IsMirrored; }
protected:
	std::shared_ptr<Texture2D> m_pTexture;
	glm::vec2 m_Pivot{};
	bool m_IsMirrored{};
};


